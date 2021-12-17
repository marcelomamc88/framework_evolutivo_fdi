disp('Compiling S-function from Hopsan model...');
mex -DHOPSAN_INTERNALDEFAULTCOMPONENTS -DHOPSAN_INTERNAL_EXTRACOMPONENTS -D_USE_MATH_DEFINES -DWIN32 -I"HopsanCore/include" -I"componentLibraries/defaultLibrary" -I"HopsanCore/dependencies/rapidxml" -I"HopsanCore/dependencies/indexingcsvparser/include" -I"HopsanCore/dependencies/libnumhop/include" -I"HopsanCore/dependencies/sundials-extra/include" -I"HopsanCore/dependencies/sundials/include" HopsanCore/src/Component.cpp HopsanCore/src/ComponentSystem.cpp HopsanCore/src/ComponentUtilities/AuxiliarySimulationFunctions.cpp HopsanCore/src/ComponentUtilities/CSVParser.cpp HopsanCore/src/ComponentUtilities/DoubleIntegratorWithDamping.cpp HopsanCore/src/ComponentUtilities/DoubleIntegratorWithDampingAndCoulumbFriction.cpp HopsanCore/src/ComponentUtilities/EquationSystemSolver.cpp HopsanCore/src/ComponentUtilities/FirstOrderTransferFunction.cpp HopsanCore/src/ComponentUtilities/HopsanPowerUser.cpp HopsanCore/src/ComponentUtilities/IntegratorLimited.cpp HopsanCore/src/ComponentUtilities/LookupTable.cpp HopsanCore/src/ComponentUtilities/ludcmp.cpp HopsanCore/src/ComponentUtilities/matrix.cpp HopsanCore/src/ComponentUtilities/PLOParser.cpp HopsanCore/src/ComponentUtilities/SecondOrderTransferFunction.cpp HopsanCore/src/ComponentUtilities/TempDirectoryHandle.cpp HopsanCore/src/ComponentUtilities/WhiteGaussianNoise.cpp HopsanCore/src/CoreUtilities/AliasHandler.cpp HopsanCore/src/CoreUtilities/ConnectionAssistant.cpp HopsanCore/src/CoreUtilities/HmfLoader.cpp HopsanCore/src/CoreUtilities/HopsanCoreMessageHandler.cpp HopsanCore/src/CoreUtilities/LoadExternal.cpp HopsanCore/src/CoreUtilities/MultiThreadingUtilities.cpp HopsanCore/src/CoreUtilities/NumHopHelper.cpp HopsanCore/src/CoreUtilities/SaveRestoreSimulationPoint.cpp HopsanCore/src/CoreUtilities/SimulationHandler.cpp HopsanCore/src/CoreUtilities/StringUtilities.cpp HopsanCore/src/HopsanEssentials.cpp HopsanCore/src/HString.cpp HopsanCore/src/Node.cpp HopsanCore/src/Nodes.cpp HopsanCore/src/Parameters.cpp HopsanCore/src/Port.cpp HopsanCore/src/Quantities.cpp HopsanCore/dependencies/libnumhop/src/Expression.cpp HopsanCore/dependencies/libnumhop/src/Helpfunctions.cpp HopsanCore/dependencies/libnumhop/src/VariableStorage.cpp HopsanCore/dependencies/sundials/src/kinsol/kinsol_spils.c HopsanCore/dependencies/sundials/src/kinsol/kinsol_ls.c HopsanCore/dependencies/sundials/src/kinsol/kinsol_io.c HopsanCore/dependencies/sundials/src/kinsol/kinsol_direct.c HopsanCore/dependencies/sundials/src/kinsol/kinsol_bbdpre.c HopsanCore/dependencies/sundials/src/kinsol/kinsol.c HopsanCore/dependencies/sundials/src/sunmatrix/dense/fsunmatrix_dense.c HopsanCore/dependencies/sundials/src/sunmatrix/dense/sunmatrix_dense.c HopsanCore/dependencies/sundials/src/nvector/serial/fnvector_serial.c HopsanCore/dependencies/sundials/src/nvector/serial/nvector_serial.c HopsanCore/dependencies/sundials/src/sundials/sundials_futils.c HopsanCore/dependencies/sundials/src/sundials/sundials_nvector_senswrapper.c HopsanCore/dependencies/sundials/src/sundials/sundials_nonlinearsolver.c HopsanCore/dependencies/sundials/src/sundials/sundials_version.c HopsanCore/dependencies/sundials/src/sundials/sundials_iterative.c HopsanCore/dependencies/sundials/src/sundials/sundials_band.c HopsanCore/dependencies/sundials/src/sundials/sundials_direct.c HopsanCore/dependencies/sundials/src/sundials/sundials_dense.c HopsanCore/dependencies/sundials/src/sundials/sundials_nvector.c HopsanCore/dependencies/sundials/src/sundials/sundials_linearsolver.c HopsanCore/dependencies/sundials/src/sundials/sundials_matrix.c HopsanCore/dependencies/sundials/src/sundials/sundials_math.c HopsanCore/dependencies/sundials/src/sunmatrix/band/sunmatrix_band.c HopsanCore/dependencies/sundials/src/sunlinsol/band/sunlinsol_band.c HopsanCore/dependencies/sundials/src/sunlinsol/dense/sunlinsol_dense.c HopsanCore/dependencies/indexingcsvparser/src/indexingcsvparser.cpp componentLibraries/defaultLibrary/defaultComponentLibraryInternal.cpp componentLibraries/extra-components.cpp F16_DS1_ALTITUDE.cpp  -output F16_DS1_ALTITUDE
disp('Finished.')
