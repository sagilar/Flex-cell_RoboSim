function __getObjectPosition__(a,b)
    -- compatibility routine, wrong results could be returned in some situations, in CoppeliaSim <4.0.1
    if b==sim.handle_parent then
        b=sim.getObjectParent(a)
    end
    if (b~=-1) and (sim.getObjectType(b)==sim.object_joint_type) and (sim.getInt32Param(sim.intparam_program_version)>=40001) then
        a=a+sim.handleflag_reljointbaseframe
    end
    return sim.getObjectPosition(a,b)
end

function __compute_xyz_flexcell__(X,Y,Z)
        Z_table_level = 0.020 
        YMIN = 0
        YMAX = 23
        XMIN = 0
        XMAX = 15
        HOLE_DIST = 0.05
        x_min = -0.072
        x_max = 1.128
        y_max = 0.731 - 0.020 -- compensation
        y_min = -0.369 - 0.020 -- compensation
        comp_x = x_max - ((Y+1)*HOLE_DIST) 
        comp_y = (y_max - ((X)*HOLE_DIST))
        comp_z = Z_table_level + Z * HOLE_DIST
        return comp_x,comp_y,comp_z
end

function __compute_inverse_xyz_flexcell__(x,y,z)
        Z_table_level = 0.020
        YMIN = 0
        YMAX = 23
        XMIN = 0
        XMAX = 15
        HOLE_DIST = 0.05
        x_min = -0.072
        x_max = 1.128
        y_max = 0.731 - 0.020 -- compensation
        y_min = -0.369 - 0.020 -- compensation

        Y = (x_max - x)/HOLE_DIST - 1
        X = (y_max - y)/HOLE_DIST
        Z = (z - Z_table_level)/HOLE_DIST
        return math.floor(X+0.5),math.floor(Y+0.5),math.floor(Z+0.5)
end

function __compute_yz_joint__(yc,zc)
        theta = math.atan(zc/yc)
        alpha = math.pi/4 + theta
        zj = (math.pow(math.pow(zc,2) + math.pow(yc,2),(1/2))) * math.cos(math.pi/2 - alpha)
        yj = (math.pow(math.pow(zc,2) + math.pow(yc,2),(1/2))) * math.sin(math.pi/2 - alpha)
        return yj,zj
end

function __compute_inverse_yz_joint__(yj,zj)
        if ((yj == 0.0) or (zj == 0.0)) then
            return yj,zj
        end
        theta = math.atan(yj/zj)
        alpha = math.pi/4 + theta
        zc = (math.pow(math.pow(zj,2) + math.pow(yj,2),(1/2))) * math.sin(math.pi/2 - alpha)
        yc = (math.pow(math.pow(zj,2) + math.pow(yj,2),(1/2))) * math.cos(math.pi/2 - alpha)
        return yc,zc
end

function sysCall_init()
    filename = 'test.csv'
    basepath = '/home/santiago/York/flex-cell/'
    sim.pauseSimulation()
    base_name = "/1_base_link_collision/"
    j0 = sim.getObject(base_name .. "11_shoulder_pan_joint") -- J0
    j1 = sim.getObject(base_name .. "18_shoulder_lift_joint") -- J1
    j2 = sim.getObject(base_name .."14_elbow_joint") -- J2
    j3 = sim.getObject(base_name .. "12_wrist_1_joint") -- J3
    j4 = sim.getObject(base_name .. "19_wrist_2_joint") -- J4
    j5 = sim.getObject(base_name .. "13_wrist_3_joint") -- J5
    
    l_fg = sim.getObject(base_name .. "16_leftFingerGripper") -- Left finger gripper (OnRobot 2FG7)
    r_fg = sim.getObject(base_name .. "15_rightFingerGripper") -- Right finger gripper (OnRobot 2FG7)
    
    print("Sim objects correctly loaded")
    

    simRemoteApi.start(8888)
    print("Start client as 'simple_bullet_remoteApi 8888 "..j0.." "..j1.." "..j2.." "..j3.." "..j4.." "..j5.." "..l_fg.." "..r_fg.."'")
    h = 0
    lifting = false
    end_effector = sim.getObject(base_name .. "8_link_2fg7_base_8__link_2fg7_box")
    positions = {}
    path = basepath..'tests/'..filename
    idx = 1

    for line in io.lines(path) do

        X,Y,Z = line:match("([^,]+),([^,]+),([^,]+)")
        n_X = tonumber(X)
        n_Y = tonumber(Y)
        n_Z = tonumber(Z)
        print(X..","..Y..","..Z)
        
        -- Perform the transformations with existing models
        --q0 =
        --q1 = 
        --q2 = 
        --q3 = 
        --q4 = 
        --q5 =
        x,yc,zc = __compute_xyz_flexcell__(n_X,n_Y,n_Z)
        yj,zj = __compute_yz_joint__(yc,zc)
	--ee_replica = sim.copyPasteObjects({end_effector},0)[1]


        sim.setObjectPosition(end_effector,-1, {x, yj, zj})
        sim.setObjectOrientation(end_effector,-1, {-5*math.pi/4, 0, 0})
        idx = idx + 1
        --positions[idx] = ee_replica
        positions[idx] = {x, yj, zj,-5*math.pi/4, 0, 0}
    end
    
end

function sysCall_actuation()
    -- put your actuation code here
    
end

function sysCall_sensing()
    -- put your sensing code here
end

function sysCall_cleanup()
    -- do some clean-up here
    output_file = basepath..'results/'..filename
    output = io.open(output_file, "w")
    for i,o in pairs(positions) do
        --pos = sim.getObjectPosition(o,-1)
        --ori = sim.getObjectOrientation(o,-1)
        --print(pos[1], pos[2], pos[3], ori[1],ori[2],ori[3])
        --output:write(pos[1],",",pos[2],",",pos[3],",",ori[1],",",ori[2],",",ori[3],"\n")
        print(o[1], o[2], o[3], o[4],o[5],o[6])
        output:write(o[1],",",o[2],",",o[3],",",o[4],",",o[5],",",o[6],"\n")
    end
    output:close()


    simRemoteApi.stop(8888)
    print("Stopped remote api")
    
end

-- See the user manual or the available code snippets for additional callback functions and details

