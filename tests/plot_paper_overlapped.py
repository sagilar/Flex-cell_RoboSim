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
df_hil = df_hil[df_hil["timestamp"]>1.0]
df_hil["timestamp"] = df_hil["timestamp"] - 1.0


df_cosim.columns = df_cosim.columns.str.replace("{mapping}.mapping", "mappingFMU")
df_cosim.columns = df_cosim.columns.str.replace("{rmq}.rmq", "RMQFMU")
df_cosim.columns = df_cosim.columns.str.replace("{dmodel}.dmodel", "dmodelFMU")

fig, axes = plt.subplots(3,2, figsize=(20,20))
ax321 = plt.subplot(3,2,1)

'''ax321.set_yticks(["", "moveDiscreteCommand"])
df_cosim.plot(x = "time",y = ["RMQFMU.controller_event"],
             figsize=(14,10),
             title = "Controller commands (RMQFMU)",
             ax=axes[0,0],
             kind="scatter")'''
x_axis_values = df_cosim["time"].to_list()
y_axis_values = df_cosim["RMQFMU.controller_event"].to_list()

y_axis_bool = [True if y == "moveDiscreteCommand" else False for y in y_axis_values]

plt.scatter(x_axis_values,y_axis_bool)
plt.title("(1) Controller commands (RMQFMU)")
plt.yticks([1.0, 0.0],["True","False"],rotation=90)
#plt.xlim([0, df_cosim["time"].max()])
#plt.ylim([0, y_max])
plt.legend(['moveDiscreteCommand'])
plt.xlabel('time [s]')
plt.ylabel('command')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,2)

df_cosim.plot(x = "time",y = ["RMQFMU.controller_event_args_0","RMQFMU.controller_event_args_1",
                                "RMQFMU.controller_event_args_2"],
             figsize=(12,12),
             title = "(2) Controller target positions (RMQFMU)",
             ax=axes[0,1],
             width=2,
             kind="bar")
plt.xlabel('time [s]')
plt.ylabel('target position (X,Y,Z)')
plt.legend(['MovementArgs.target_X','MovementArgs.target_Y','MovementArgs.target_Z'])
plt.grid()
plt.tight_layout()

plt.subplot(3,2,3)

df_cosim.plot(x = "time",y = ["dmodelFMU.d_model_event_args_0","dmodelFMU.d_model_event_args_1",
                                    "dmodelFMU.d_model_event_args_2"],
             figsize=(12,12),
             title = "(3) Operation arguments (d-modelFMU)",
             ax=axes[1,0])
plt.legend(['target_X','target_Y','target_Z'])
plt.xlabel('time [s]')
plt.ylabel('position (X,Y,Z)')
plt.grid()
plt.tight_layout()

plt.subplot(3,2,4)
df_cosim.plot(x = "time",y = ["mappingFMU.j1"],
             figsize=(12,12),
             ax=axes[1,1])

df_hil.plot(x = "timestamp",y = ["actual_q_1"],
             figsize=(12,12),
             ax=axes[1,1])
plt.title('(4) Joint positions')
plt.xlabel('time [s]')
plt.ylabel('position [rad]')
plt.legend(['Joint 1 (CoppeliaSim)','Joint 1 (UR5e)'])
plt.grid()
plt.tight_layout()


plt.subplot(3,2,5)
df_cosim.plot(x = "time",y = ["mappingFMU.qd1"],
             figsize=(12,12),
             ax=axes[2,0])


df_hil.plot(x = "timestamp",y = ["actual_qd_1"],
             figsize=(12,12),
             ax=axes[2,0])
plt.title('(5) Joint velocities')
plt.xlabel('time [s]')
plt.ylabel('velocity [rad/s]')
plt.legend(['Joint 1 (CoppeliaSim)','Joint 1 (UR5e)'])
plt.grid()
plt.tight_layout()

plt.subplot(3,2,6)
df_cosim.plot(x = "time",y = ["mappingFMU.t1"],
             figsize=(12,12),
             ax=axes[2,1])

df_hil.plot(x = "timestamp",y = ["actual_TCP_force_1"],
             figsize=(12,12),
             ax=axes[2,1])
plt.title('(6) Joint forces')
plt.xlabel('time [s]')
plt.ylabel('force [N]')
plt.legend(['Joint 1 (CoppeliaSim)','Joint 1 (UR5e)'])
plt.grid()
plt.tight_layout()


fig.savefig('experiment_plot_rmq_paper_overlapped.pdf', dpi=300)
fig.savefig('experiment_plot_rmq_paper_overlapped.png', dpi=300)
