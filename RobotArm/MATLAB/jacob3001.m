% takes a 3 by 1 matrix of joint values and return a 6 by 3 jacobian
% matrix according to the joint configuration
function J = jacob3001(jointConfiguration)

    % allocate memories
    Jv = zeros(3,3);
    Jw = zeros(3,3);

    % link length
    l1 = 0.15;
    l2 = 0.3;
    l3 = 0.25;

    % calculate each homogeneous transformation matrix with respect
    % to the previous frame
    A1 = dh2mat([jointConfiguration(1), l1, 0, -90]);
    A2 = dh2mat([jointConfiguration(2)-90, 0, l2 , 0]);
    A3 = dh2mat([jointConfiguration(3)+90, 0, l3, 0]);

    % calculate each homogeneous transformation matrix with respect
    % to the base
    T1 = A1;
    T2 = T1 * A2;
    T3 = T2 * A3;

    % record end-effector positions
    O0 = [0 0 0]'; % origin of the base frame
    O1 = T1(1:3,4);
    O2 = T2(1:3,4);
    On = T3(1:3,4);

    Z0 = [0 0 1]'; % z axis
    Z1 = T1(1:3,3);
    Z2 = T2(1:3,3);

    % linear velocities
    Jv(:,1) = cross(Z0,On-O0);
    Jv(:,2) = cross(Z1,On-O1);
    Jv(:,3) = cross(Z2,On-O2);

    % angular velocities
    Jw(:,1) = Z0;
    Jw(:,2) = Z1;
    Jw(:,3) = Z2;

    J = [Jv;Jw];
end