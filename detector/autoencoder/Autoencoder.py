from torch import nn

class Autoencoder(nn.Module):
    def __init__(self):
        super().__init__()
        self.encoder = nn.Sequential(
            nn.Linear(54, 32),
            nn.ReLU(),
            nn.Linear(32, 9),
        )

        self.decoder = nn.Sequential(
            nn.Linear(9, 32),
            nn.ReLU(),
            nn.Linear(32, 54),
            nn.Tanh()
        )

    def forward(self, x):
        return self.decoder(self.encoder(x))