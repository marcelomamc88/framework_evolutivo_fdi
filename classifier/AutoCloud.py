import numpy as np
import math
from numpy import linalg as LA
from scipy.spatial import distance


#### CLOUD ####
class Cloud:

    def __init__(self, sample=[], name='Default Class'):
        self.name = name
        self.var = 0
        self.n = 0
        self.covmat = []

        if (len(sample) > 0):
            self.mean = sample
            self.n = 1
            self.covmat = np.zeros((sample.shape[0], sample.shape[0]))

    def updateCloud(self, mu=[], var=0, n=0, covmat=[]):
        self.mean = mu
        self.var = var
        self.n = n
        self.covmat = covmat

    def addPoint(self, sample=[]):
        if (self.n == 0):
            self.n = 1
            self.mean = sample
            self.var = 0
            self.covmat = np.zeros((self.mean.shape[0], self.mean.shape[0]))
        else:
            self.n = self.n + 1
            self.mean = self.calculate_mean(sample, self.n)
            self.var = self.calculate_variance(sample, self.n, self.mean)
            self.covmat = self.calculate_variance_matrix(sample, self.n, self.mean)


    def calculateZeta(self, sample=[], similarity_measure='euclidean'):
        if self.n == 0:
            zeta = math.inf
            return zeta

        n_ = self.n + 1
        mean_ = self.calculate_mean(sample, n_)
        var_ = self.calculate_variance(sample, n_, mean_)
        covmat_ = self.calculate_variance_matrix(sample, n_, mean_)


        if (similarity_measure.lower() == 'euclidean'):
            ksi = np.maximum(self.calculate_eccentricity(sample, self.n, mean_, var_), 0.0001)
        else:
            ksi = np.maximum(self.calculate_eccentricity(sample, n_, mean_, var_, covmat_, 'mahalanobis'), 0.0001)

        zeta = ksi / 2
        return zeta

    def calculate_mean(self, sample, n):
        return ((n - 1) / n) * self.mean + (1 / n) * sample

    def calculate_variance(self, sample, n, mean):
        return ((n - 1) / n) * self.var + (1 / (n)) * LA.norm(sample - mean) ** 2

    def calculate_variance_matrix(self, sample, n, mean):
        a = (n - 1) / n
        b = a * self.covmat
        c = [sample - mean]
        d = np.transpose(c)
        e = (1 / n) * d    ##TALVEZ SEJA 1 / (n-1)

        f = b + e * c

        return f

    def calculate_eccentricity(self, sample, n, mean, variance, covmat = [], similarity_measure = 'euclidean'):

        a = 1 / n

        if (similarity_measure == 'euclidean'):
            b = [mean - sample]
            c = np.transpose(b)
            d = n * variance
            e = np.dot(b, c)
            f = e / d

            r = distance.euclidean(sample, mean)

            ksi = a + f
        else: # mahalanobis_formula => (sample - mean).T * covmat*-1 * (sample - mean)

            d_mahalanobis = np.zeros((1,1), dtype=float) + distance.mahalanobis(mean, sample, LA.pinv(covmat))**2

            h = n * len(mean) #nao entendi para que isso - parece a ponderacao do n elementos pela qtd de dimensoes
            m = d_mahalanobis / h

            ksi = a + m

        return ksi

###########################################################################
###########################################################################
################################ AUTOCLOUD ################################
###########################################################################
###########################################################################
class AutoCloud:
        
    def __init__(self, m = 2, similarity_measure = 'euclidean', auto_merge = True, display = False):
        self.k = 0
        self.cloudList = []
        self.predictions = {}
        self.predictions_by_sample = {}
        self.initialize_intersection_list()
        self.initialize_intersection_matrix()
        self.contMerge = 0
        self.dimension = 0
        self.similarityMeasure = similarity_measure
        self.autoMerge = auto_merge
        self.m = m
        self.display = display

    def run(self, sample = [], label = None):

        if (self.dimension == 0):
            self.dimension = sample.shape[0]
        else:
            if (self.dimension != sample.shape[0]):
                raise Exception('The dimension of the current data sample is different from the points read so far.')

        if (label != None): #para supervisionado - aqui temos também o Y (label) da amostra

            while (len(self.cloudList) < label): #cria a qtd de classes
                self.create_cloud(sample)

            self.cloudList[label - 1].addPoint(sample)
            self.k = self.k + 1

            self.initialize_intersection_list()
            self.membershipList = [0] * len(self.cloudList)
            self.membershipList[label - 1] = 1
            self.intersectionList[label - 1] = 1
            self.initialize_intersection_matrix()

            return label, self.membershipList

        else:
            self.k = self.k + 1
            self.initialize_intersection_list()

            if (self.k == 1):
                self.cloudList.append(Cloud(sample = sample, name = 'Class 1'))
                self.initialize_intersection_list()
                self.initialize_intersection_matrix()
                self.membershipList = [1]
            elif (self.k == 2):
                self.cloudList[0].addPoint(sample)
                self.membershipList = [1]
            elif (self.k >= 3):
                createCloud = True
                tauList = np.zeros((len(self.cloudList), 1))

                for i_cloud, cloud in enumerate(self.cloudList):
                    zeta = cloud.calculateZeta(sample, self.similarityMeasure) #??eccentricity | ?? norm_eccentricity
                    tau = 1 - zeta #??typicality
                    tauList[i_cloud] = tau

                    if (self.calculate_sample_belongs_to_cloud(zeta, cloud.n)):
                        cloud.addPoint(sample)
                        self.intersectionList[i_cloud] = 1
                        createCloud = False
                    else:
                        self.intersectionList[i_cloud] = 0

                self.membershipList = tauList / sum(tauList)

                ### NEW CLOUD ###
                if (createCloud == True):
                    self.create_cloud(sample)

        amax = np.amax(self.membershipList)
        where = np.where(self.membershipList == amax)
        y_label = where[0][0]+1

        if (self.autoMerge):
            self.mergeClouds()

        return y_label, self.membershipList

    def mergeClouds(self):
        i = 0

        i_end = len(self.cloudList) - 1
        while (i < i_end):

            merge = False

            j_end = np.arange(i + 1, len(self.cloudList)).reshape(-1)
            for j in j_end:
                if (self.intersectionList[i] == 1 and self.intersectionList[j] == 1):
                    self.intersectionMatrix[i,j] = self.intersectionMatrix[i,j] + 1

                ### recover information about clouds to be merged ###
                n_i = self.cloudList[i].n
                n_j = self.cloudList[j].n
                mean_i = self.cloudList[i].mean
                mean_j = self.cloudList[j].mean
                var_i = self.cloudList[i].var
                var_j = self.cloudList[j].var
                covmat_i = self.cloudList[i].covmat
                covmat_j = self.cloudList[j].covmat
                nint = self.intersectionMatrix[i,j]

                if (nint > (n_i - nint) or nint > (n_j - nint)):
                    ### merge
                    if (self.display):
                        print('Merging clouds ' + str(i+1) + ' and ' + str(j+1) + ' at instant ' + str(self.k))
                    ### calculate state of new cloud
                    n = n_i + n_j - nint
                    mean = ((n_i * mean_i) + (n_j * mean_j)) / (n_i + n_j)
                    var = ((n_i - 1) * var_i + (n_j - 1) * var_j) / (n_i + n_j - 2)
                    covmat = ((n_i - 1) * covmat_i + (n_j - 1) * covmat_j) / (n_i + n_j - 2)
                    ### create new cloud cloud ###
                    newCloud = Cloud()
                    newCloud.updateCloud(mean, var, n, covmat)
                    newCloud.name = 'Class ' + str(i+1) + '/' + str(j+1)

                    ### update intersection list ###
                    v_il1 = self.intersectionList[0: i]
                    v_il2 = np.array([1])
                    v_il3 = self.intersectionList[i + 1: j]
                    v_il4 = self.intersectionList[j + 1: np.size(self.intersectionList)]
                    self.intersectionList = np.concatenate((v_il1, v_il2, v_il3, v_il4), axis=None)

                    ## update cloud list ###
                    if (self.display):
                        print("Cloud (label) : " + str(i))
                    v_c1 = self.cloudList[0: i]
                    v_c2 = np.array([newCloud])
                    v_c3 = self.cloudList[i + 1: j]
                    v_c4 = self.cloudList[j + 1: np.size(self.cloudList)]
                    self.cloudList = np.concatenate((v_c1, v_c2, v_c3, v_c4), axis=None)

                    ### update intersection matrix ###
                    A = self.intersectionMatrix

                    #remover linha
                    vb1_0 = A[0: i, :]
                    vb2 = np.zeros((1, len(A)))
                    vb3 = A[i + 1: j, :]
                    vb4 = A[j + 1: len(A), :]
                    B = np.concatenate(([vb1_0, vb2, vb3, vb4]))

                    #remover coluna
                    vb1_1 = B[:, 0: i]
                    vb2 = np.zeros((len(B), 1))
                    vb3 = B[:, i + 1: j]
                    vb4 = B[:, j + 1: len(A)] ### acho que deveria ser LEN de B
                    B = np.concatenate(([vb1_1, vb2, vb3, vb4]), axis=1)

                    # calc nova coluna
                    col = (A[:, i] + A[:, j]) * (A[:, i] * A[:, j] != 0)
                    C = np.concatenate((col[0: j], col[j + 1: np.size(col)]))

                    # calc nova linha
                    lin = (A[i, :] + A[j, :]) * (A[i, :] * A[j, :] != 0)
                    L = np.concatenate((lin[0: j], lin[j + 1: np.size(lin)]))

                    #atualizar coluna
                    B[:,i] = C

                    #atualizar linha
                    B[i,:] = L

                    vb1_2 = A[[i], i+1 : j]
                    vb2 = A[i+1 : j, [j]]
                    vb3 = np.transpose(vb2)

                    B[[i], i+1 : j] = vb1_2 + vb3

                    self.intersectionMatrix = B

                    merge = True
                    self.contMerge = self.contMerge + 1
                    break

            if (merge == True):
                i = 1
            else:
                i = i + 1


    def initialize_intersection_matrix(self):
        if (len(self.cloudList) == 0):
            self.intersectionMatrix = np.zeros((1, 1))
        else:
            self.intersectionMatrix = np.zeros((len(self.cloudList), len(self.cloudList)))

    def initialize_intersection_list(self):
        if (len(self.cloudList) == 0):
            self.intersectionList = []
        else:
            self.intersectionList = [0] * len(self.cloudList)


    def calculateThreshold(self, s=None):
        if (self.similarityMeasure.lower() == 'euclidean'):
            th = (self.m ** 2 + 1) / (2 * (s))
        else:
            if (self.similarityMeasure.lower() == 'mahalanobis'):
                th = (self.m ** 2 + self.dimension) / (2 * (s) * self.dimension)

        threshold = th
        return threshold

    def create_cloud(self, sample):
        cloud_number = len(self.cloudList) + 1
        if (self.display):
            print('Creating cloud ' + str(cloud_number) + ' at instant ' + str(self.k))

        self.cloudList = np.append(self.cloudList, [Cloud(sample, 'Class ' + str(cloud_number))], axis=0)
        self.intersectionList.append(1)
        self.expand_intersection_matrix_with_zeros()

    def calculate_sample_belongs_to_cloud(self, zeta, cloud_n):
        return (zeta < math.inf and zeta <= self.calculateThreshold(cloud_n))

    def expand_intersection_matrix_with_zeros(self):
        self.intersectionMatrix = np.pad(self.intersectionMatrix, ((0, 1), (0, 1)), mode='constant', constant_values=0)