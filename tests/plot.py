# Author: Santiago Gil
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

filename = "outputs_UR3e_DTLab.csv"

font = {'font.family' : 'monospace',
        'font.weight' : 'bold',
        'axes.titlesize'   : 18,
        'axes.labelsize'   : 14,
        'legend.fontsize' : 10,
        'xtick.labelsize': 10,
        'ytick.labelsize': 10,
       }

plt.rcParams.update(font)
df_cosim = pd.read_csv(filename)
df_cosim.fillna("",inplace=True)


'''
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
'''

"""df_cosim.columns = df_cosim.columns.str.replace("{mapping}.mapping", "PlatformMappingFMU")
df_cosim.columns = df_cosim.columns.str.replace("{rmq}.rmq", "RMQFMU")
df_cosim.columns = df_cosim.columns.str.replace("{dmodel}.dmodel", "dmodelFMU")

fig, axes = plt.subplots(3,2, figsize=(20,14))
ax321 = plt.subplot(3,2,1)

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

plt.subplot(3,2,2)

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

plt.subplot(3,2,3)

df_cosim.plot(x = "time",y = ["dmodelFMU.d_model_event_args_0","dmodelFMU.d_model_event_args_1",
                                    "dmodelFMU.d_model_event_args_2"],
             figsize=(12,12),
             title = "Discrete positions (D-Model)",
             ax=axes[1,0])
plt.xlabel('time [s]')
plt.ylabel('position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,4)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.j0","PlatformMappingFMU.j1",
                                    "PlatformMappingFMU.j2","PlatformMappingFMU.j3",
                                   "PlatformMappingFMU.j4","PlatformMappingFMU.j5"],
             figsize=(12,12),
             title = "Joint positions (CoppeliaSim)",
             ax=axes[1,1])
plt.xlabel('time [s]')
plt.ylabel('position [rad]')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,5)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.qd0","PlatformMappingFMU.qd1",
                                    "PlatformMappingFMU.qd2","PlatformMappingFMU.qd3",
                                   "PlatformMappingFMU.qd4","PlatformMappingFMU.qd5"],
             figsize=(12,12),
             title = "Joint velocities (CoppeliaSim)",
             ax=axes[2,0])
plt.xlabel('time [s]')
plt.ylabel('velocity [rad/s]')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,6)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.t0","PlatformMappingFMU.t1",
                                    "PlatformMappingFMU.t2","PlatformMappingFMU.t3",
                                   "PlatformMappingFMU.t4","PlatformMappingFMU.t5"],
             figsize=(12,12),
             title = "Joint forces (CoppeliaSim)",
             ax=axes[2,1])
plt.xlabel('time [s]')
plt.ylabel('force [N]')
plt.grid()
plt.tight_layout()

fig.savefig('experiment_plot_rmq.pdf', dpi=300)
fig.savefig('experiment_plot_rmq.png', dpi=300)"""

df_cosim.columns = df_cosim.columns.str.replace("{mapping}.mapping", "PlatformMappingFMU")
df_cosim.columns = df_cosim.columns.str.replace("{controller}.controller", "ControllerFMU")
df_cosim.columns = df_cosim.columns.str.replace("{dmodel}.dmodel", "dmodelFMU")

fig, axes = plt.subplots(3,2, figsize=(14,14))
ax321 = plt.subplot(3,2,1)

'''ax321.set_yticks(["", "moveDiscreteCommand"])
df_cosim.plot(x = "time",y = ["ControllerFMU.controller_event"],
             figsize=(14,10),
             title = "Controller commands (ControllerFMU)",
             ax=axes[0,0],
             kind="scatter")'''
x_axis_values = df_cosim["time"].to_list()
y_axis_values = df_cosim["ControllerFMU.controller_event"].to_list()
plt.scatter(x_axis_values,y_axis_values,label='ControllerFMU.controller_event')
plt.title("Controller commands (ControllerFMU)")
plt.yticks(rotation=90)
#plt.xlim([0, df_cosim["time"].max()])
#plt.ylim([0, y_max])
plt.xlabel('time [s]')
plt.ylabel('command')
plt.legend()
plt.grid()
plt.tight_layout()

plt.subplot(3,2,2)

df_cosim.plot(x = "time",y = ["ControllerFMU.controller_event_args_0","ControllerFMU.controller_event_args_1",
                                "ControllerFMU.controller_event_args_2"],
             figsize=(12,12),
             title = "Controller target pos.(ControllerFMU)",
             ax=axes[0,1],
             width=2,
             kind="bar")
plt.xlabel('time [s]')
plt.ylabel('target position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,3)

df_cosim.plot(x = "time",y = ["dmodelFMU.d_model_event_args_0","dmodelFMU.d_model_event_args_1",
                                    "dmodelFMU.d_model_event_args_2"],
             figsize=(12,12),
             title = "Discrete positions (d-modelFMU)",
             ax=axes[1,0])
plt.xlabel('time [s]')
plt.ylabel('position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,4)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.j0","PlatformMappingFMU.j1",
                                    "PlatformMappingFMU.j2","PlatformMappingFMU.j3",
                                   "PlatformMappingFMU.j4","PlatformMappingFMU.j5"],
             figsize=(12,12),
             title = "Joint positions (UR3e)",
             ax=axes[1,1])
plt.xlabel('time [s]')
plt.ylabel('position [rad]')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,5)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.qd0","PlatformMappingFMU.qd1",
                                    "PlatformMappingFMU.qd2","PlatformMappingFMU.qd3",
                                   "PlatformMappingFMU.qd4","PlatformMappingFMU.qd5"],
             figsize=(12,12),
             title = "Joint velocities (UR3e)",
             ax=axes[2,0])
plt.xlabel('time [s]')
plt.ylabel('velocity [rad/s]')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,6)
df_cosim.plot(x = "time",y = ["PlatformMappingFMU.t0","PlatformMappingFMU.t1",
                                    "PlatformMappingFMU.t2","PlatformMappingFMU.t3",
                                   "PlatformMappingFMU.t4","PlatformMappingFMU.t5"],
             figsize=(12,12),
             title = "Joint forces (UR3e)",
             ax=axes[2,1])
plt.xlabel('time [s]')
plt.ylabel('force [N]')
plt.grid()
plt.tight_layout()


fig.savefig('experiment_plot_normq_UR3e_DTLab.pdf', dpi=300)
fig.savefig('experiment_plot_normq_UR3e_DTLab.png', dpi=300)
