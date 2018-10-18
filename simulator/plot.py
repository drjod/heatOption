import pandas as pd
import matplotlib.pyplot as plt

frame = pd.read_table('output.dat', sep='\s+', names=['S', 'C', 'Delta', 'Gamma'])

fig, ax = plt.subplots()
ax.plot(frame['S'], frame['C'], label='C')
ax.plot(frame['S'], frame['Delta'], label='Delta')
ax.plot(frame['S'], frame['Gamma'], label='Gamma')

ax.grid(True)

plt.legend()


plt.show()
