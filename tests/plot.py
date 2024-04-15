# Author: Santiago Gil
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

filename = "outputs_cosim.csv"

font = {'font.family' : 'monospace',
        'font.weight' : 'bold',
        'axes.titlesize'   : 18,
        'axes.labelsize'   : 14,
        'legend.fontsize' : 10,
        'xtick.labelsize': 8,
        'ytick.labelsize': 8,
       }

plt.rcParams.update(font)
df_cosim = pd.read_csv(filename)


fig, axes = plt.subplots(2,2, figsize=(16,12))
plt.subplot(2,2,1)

df_cosim.plot(x = "time",y = ["{dmodel}.dmodel.d_model_event_args_0","{dmodel}.dmodel.d_model_event_args_1",
                                    "{dmodel}.dmodel.d_model_event_args_2"],
             figsize=(14,10),
             title = "Discrete positions (D-Model)",
             ax=axes[0,0])
plt.xlabel('time [s]')
plt.ylabel('hole combination')
plt.grid()
plt.tight_layout()

plt.subplot(2,2,2)
df_cosim.plot(x = "time",y = ["{mapping}.mapping.j0","{mapping}.mapping.j1",
                                    "{mapping}.mapping.j2","{mapping}.mapping.j3",
                                   "{mapping}.mapping.j4","{mapping}.mapping.j5"],
             figsize=(14,10),
             title = "Co-sim UR5e joint positions (CoppeliaSim)",
             ax=axes[0,1])
plt.xlabel('time [s]')
plt.ylabel('radians')
plt.grid()
plt.tight_layout()

plt.subplot(2,2,3)
df_cosim.plot(x = "time",y = ["{mapping}.mapping.qd0","{mapping}.mapping.qd1",
                                    "{mapping}.mapping.qd2","{mapping}.mapping.qd3",
                                   "{mapping}.mapping.qd4","{mapping}.mapping.qd5"],
             figsize=(14,10),
             title = "Co-sim UR5e joint velocities (CoppeliaSim)",
             ax=axes[1,0])
plt.xlabel('time [s]')
plt.ylabel('radians/s')
plt.grid()
plt.tight_layout()

plt.subplot(2,2,4)
df_cosim.plot(x = "time",y = ["{mapping}.mapping.t0","{mapping}.mapping.t1",
                                    "{mapping}.mapping.t2","{mapping}.mapping.t3",
                                   "{mapping}.mapping.t4","{mapping}.mapping.t5"],
             figsize=(14,10),
             title = "Co-sim UR5e joint force (CoppeliaSim)",
             ax=axes[1,1])
plt.xlabel('time [s]')
plt.ylabel('N')
plt.grid()
plt.tight_layout()

fig.savefig('experiment_plot.pdf', dpi=300)
fig.savefig('experiment_plot.png', dpi=300)
