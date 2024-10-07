# Author: Santiago Gil
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

filename_sim = "outputs_UR5e_CoppeliaSim_rmq_20s.csv"
filename_hil = "ur5e_flexcell_rmq_20s.csv"

'''font = {'font.family' : 'monospace',
        'font.weight' : 'bold',
        'axes.titlesize'   : 18,
        'axes.labelsize'   : 14,
        'legend.fontsize' : 10,
        'xtick.labelsize': 10,
        'ytick.labelsize': 10,
       }'''

font = {'font.family' : 'monospace',
        'font.weight' : 'bold',
        'axes.titlesize'   : 14,
        'axes.labelsize'   : 12,
        'legend.fontsize' : 8,
        'xtick.labelsize': 8,
        'ytick.labelsize': 8,
       }

plt.rcParams.update(font)
df_cosim = pd.read_csv(filename_sim)
df_cosim.fillna("",inplace=True)

df_hil = pd.read_csv(filename_hil,sep=" ")
df_hil.fillna("",inplace=True)


#df_hil = df_hil[(df_hil["timestamp"]>14842) & (df_hil["timestamp"]<14852)]
df_hil["timestamp"] = df_hil["timestamp"].astype(float)-7482.363
#df_hil = df_hil[df_hil["timestamp"]<20.0]
#df_hil = df_hil[df_hil["timestamp"]>4.0]
#df_hil["timestamp"] = df_hil["timestamp"] - 4.0


df_cosim.columns = df_cosim.columns.str.replace("{mapping}.mapping", "PlatformMappingFMU")
df_cosim.columns = df_cosim.columns.str.replace("{rmq}.rmq", "RMQFMU")
df_cosim.columns = df_cosim.columns.str.replace("{dmodel}.dmodel", "dmodelFMU")

fig, axes = plt.subplots(3,3, figsize=(28,20))
ax321 = plt.subplot(3,3,1)

'''ax321.set_yticks(["", "moveDiscreteCommand"])
df_cosim.plot(x = "time",y = ["RMQFMU.controller_event"],
             figsize=(14,10),
             title = "Controller commands (RMQFMU)",
             ax=axes[0,0],
             kind="scatter")'''
x_axis_values = df_cosim["time"].to_list()
y_axis_values = df_cosim["RMQFMU.controller_event"].to_list()
plt.scatter(x_axis_values,y_axis_values,label='RMQFMU.controller_event')
plt.title("Controller commands (RMQFMU)")
plt.yticks(rotation=90)
#plt.xlim([0, df_cosim["time"].max()])
#plt.ylim([0, y_max])
plt.xlabel('time [s]')
plt.ylabel('command')
plt.legend()
plt.grid()
plt.tight_layout()

plt.subplot(3,3,2)

df_cosim.plot(x = "time",y = ["RMQFMU.controller_event_args_0","RMQFMU.controller_event_args_1",
                                "RMQFMU.controller_event_args_2"],
             figsize=(12,12),
             title = "Controller target positions (RMQFMU)",
             ax=axes[0,1],
             width=2,
             kind="bar")
plt.xlabel('time [s]')
plt.ylabel('target position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,3)

df_cosim.plot(x = "time",y = ["dmodelFMU.d_model_event_args_0","dmodelFMU.d_model_event_args_1",
                                    "dmodelFMU.d_model_event_args_2"],
             figsize=(12,12),
             title = "Discrete positions (D-Model)",
             ax=axes[0,2])
plt.xlabel('time [s]')
plt.ylabel('position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,4)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.j0","PlatformMappingFMU.j1",
                                    "PlatformMappingFMU.j2","PlatformMappingFMU.j3",
                                   "PlatformMappingFMU.j4","PlatformMappingFMU.j5"],
             figsize=(12,12),
             title = "Joint positions (CoppeliaSim)",
             ax=axes[1,0])
plt.xlabel('time [s]')
plt.ylabel('position [rad]')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,5)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.qd0","PlatformMappingFMU.qd1",
                                    "PlatformMappingFMU.qd2","PlatformMappingFMU.qd3",
                                   "PlatformMappingFMU.qd4","PlatformMappingFMU.qd5"],
             figsize=(12,12),
             title = "Joint velocities (CoppeliaSim)",
             ax=axes[1,1])
plt.xlabel('time [s]')
plt.ylabel('velocity [rad/s]')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,6)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.t0","PlatformMappingFMU.t1",
                                    "PlatformMappingFMU.t2","PlatformMappingFMU.t3",
                                   "PlatformMappingFMU.t4","PlatformMappingFMU.t5"],
             figsize=(12,12),
             title = "Joint forces (CoppeliaSim)",
             ax=axes[1,2])
plt.xlabel('time [s]')
plt.ylabel('force [N]')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,7)
df_hil.plot(x = "timestamp",y = ["actual_q_0","actual_q_1",
                                    "actual_q_2","actual_q_3",
                                   "actual_q_4","actual_q_5"],
             figsize=(12,12),
             title = "Joint positions (UR5e)",
             ax=axes[2,0])
plt.xlabel('time [s]')
plt.ylabel('position [rad]')
plt.grid()
plt.tight_layout()

plt.subplot(3,3,8)
df_hil.plot(x = "timestamp",y = ["actual_qd_0","actual_qd_1",
                                    "actual_qd_2","actual_qd_3",
                                   "actual_qd_4","actual_qd_5"],
             figsize=(12,12),
             title = "Joint velocities (UR5e)",
             ax=axes[2,1])
plt.xlabel('time [s]')
plt.ylabel('velocity [rad/s]')
plt.grid()
plt.tight_layout()


plt.subplot(3,3,9)
df_hil.plot(x = "timestamp",y = ["actual_TCP_force_0","actual_TCP_force_1",
                                    "actual_TCP_force_2","actual_TCP_force_3",
                                   "actual_TCP_force_4","actual_TCP_force_5"],
             figsize=(12,12),
             title = "Joint forces (UR5e)",
             ax=axes[2,2])
plt.xlabel('time [s]')
plt.ylabel('force [N]')
plt.grid()
plt.tight_layout()


fig.savefig('experiment_plot_rmq_paper.pdf', dpi=300)
fig.savefig('experiment_plot_rmq_paper.png', dpi=300)
