% takes n joint configurations as inputs in the form of an n × 1 vector joint angles
% return a 4 × 4 homogeneous transformation matrix representing the position and orientation of 
% the end-effector frame with respect to the base frame 
function T = fk3001(jointConfiguration)

    % joint configurations are thetas in DH parameters
    theta(1) = jointConfiguration(1);
    theta(2) = jointConfiguration(2);
    theta(3) = jointConfiguration(3);

    % link length
    l1 = 0.15;
    l2 = 0.3;
    l3 = 0.25;

    % calculate the transformation matrix of each step
    A1 = dh2mat([theta(1), l1, 0, -90]);
    A2 = dh2mat([theta(2)-90, 0, l2 , 0]);
    A3 = dh2mat([theta(3)+90, 0, l3, 0]);

    % calculate the transformation matrix with respect to base
    % frame
    T = A1 * A2 * A3;
end