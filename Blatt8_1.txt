import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import multivariate_normal

# Definition der zentrierten bivariaten Normalverteilung
mu = np.array([0, 0]) # Mittelwert
Sigma = np.array([[3, 2], [2, 3]]) # Kovarianzmatrix
rv = multivariate_normal(mean=mu, cov=Sigma) # Random Variable simulieren mit entsprechender Dichte

# Zielverteilung: bivariate Normalverteilung, bedingt auf {x > 2, y > 2}
def target_density(x):
    if np.all(x > 2):
        return rv.pdf(x) # Dichte nur im Akzeptanzbereich
    else:
        return 0.0 # Dichte ist 0 außerhalb des Akzeptanzbereichs

# -----------------------------
# 1. Acceptance-Rejection Sampling
# -----------------------------

def acceptance_rejection(n_samples):
    samples = []
    M = rv.pdf([2, 2])  # Obere Schranke für Dichte im Akzeptanzbereich
    while len(samples) < n_samples:
        proposal = rv.rvs() # Vorschlag aus der Normalverteilung
        u = np.random.uniform(0, M) # Zufallszahl für Akzeptanz
        if u < target_density(proposal): # Akzeptanzkriterium
            samples.append(proposal)  # nur die, die das Kriterium erfüllen
    return np.array(samples)

# -----------------------------
# 2. Metropolis-Hastings mit Random Walk
# -----------------------------

def metropolis_hastings(n_samples, start, proposal_width=1.0):
    samples = []
    x = start
    for _ in range(n_samples):
        proposal = x + np.random.uniform(-proposal_width, proposal_width, size=2) # Vorschlag aus dem Random Walk
        if target_density(x) == 0: # Wenn der Startpunkt außerhalb des Akzeptanzbereichs ist
            alpha = 1.0  # erster Schritt
        else:
            alpha = min(1.0, target_density(proposal) / target_density(x)) # Akzeptanzwahrscheinlichkeit, abhängig von der Dichte
        if np.random.rand() < alpha: # Akzeptanzkriterium
            x = proposal # dann akzeptiere den Vorschlag
        samples.append(x)
    return np.array(samples)

# -----------------------------
# Simulation
# -----------------------------

n = 1000

# 1. Acceptance-Rejection
samples_ar = acceptance_rejection(n)

# 2. Metropolis-Hastings
start_point = np.array([3.0, 3.0])  # sinnvoll gewählter Startpunkt im gültigen Bereich
samples_mh = metropolis_hastings(n, start_point)

# -----------------------------
# Visualisierung
# -----------------------------

# Dichte-Plot zur Orientierung
x, y = np.mgrid[-1:6:.1, -1:6:.1]
pos = np.dstack((x, y))
z = rv.pdf(pos)

plt.figure(figsize=(15, 5))

# Plot 1: Dichte mit Akzeptanzbereich
plt.subplot(1, 3, 1)
plt.contourf(x, y, z, levels=30, cmap='viridis')
plt.axvline(2, color='red', linestyle='--')
plt.axhline(2, color='red', linestyle='--')
plt.title("Zielverteilung (mit Schranke bei x,y > 2)")

# Plot 2: Acceptance-Rejection Samples
plt.subplot(1, 3, 2)
plt.scatter(samples_ar[:, 0], samples_ar[:, 1], s=10, alpha=0.5)
plt.title("Samples (Acceptance-Rejection)")
plt.xlim(0, 6)
plt.ylim(0, 6)

# Plot 3: Metropolis-Hastings Pfad
plt.subplot(1, 3, 3)
plt.plot(samples_mh[:, 0], samples_mh[:, 1], alpha=0.7)
plt.scatter(samples_mh[:, 0], samples_mh[:, 1], s=5, color='blue', alpha=0.5)
plt.title("MH-Pfad der Markovkette")
plt.xlim(0, 6)
plt.ylim(0, 6)

plt.tight_layout()
plt.show()