function plot_arm(jointConfiguration)
    
    % the joint values are thetas in DH parameters
    theta(1) = jointConfiguration(1);
    theta(2) = jointConfiguration(2);
    theta(3) = jointConfiguration(3);

    % link length
    l1 = 150;
    l2 = 300;
    l3 = 250;

    % calculate each homogeneous transformation matrix with respect
    % to the previous frame
    A1 = dh2mat([theta(1), l1, 0, -90]);
    A2 = dh2mat([theta(2)-90, 0, l2 , 0]);
    A3 = dh2mat([theta(3)+90, 0, l3, 0]);

    % calculate each homogeneous transformation matrix with respect
    % to the base
    T1 = A1;
    T2 = T1 * A2;
    T3 = T2 * A3;

    % record end-effector positions
    J0 = [0 0 0]; % origin of the base frame
    J1 = T1(1:3,4)';
    J2 = T2(1:3,4)';
    J3 = T3(1:3,4)';
    Js = [J1;J2;J3]; % create a matrix of end-effector positions

    line(J0,J1); % plot a line that connects the origin of the base and first joint
    plot3([J0(1) J1(1)],[J0(2) J1(2)],[J0(3) J1(3)],'k',"LineWidth",1);
    hold on;
    line(Js(:,1),Js(:,2),Js(:,3)); % plot a line that connects all three joints
    plot3(Js(:,1),Js(:,2),Js(:,3),'k',"LineWidth",1);

    % plot the joint positions
    plot3(J1(1),J1(2),J1(3),'.','MarkerSize',16);
    plot3(J2(1),J2(2),J2(3),'.','MarkerSize',16);
    plot3(J3(1),J3(2),J3(3),'.','MarkerSize',16);

    % calculate the coordinate frame of each joint
    X0 = [1;0;0] .* 30;
    Y0 = [0;1;0] .* 15;
    Z0 = [0;0;1] .* 30;
    X1 = T1(1:3,1:3) * [1;0;0] .* 30;
    Y1 = T1(1:3,1:3) * [0;1;0] .* 15;
    Z1 = T1(1:3,1:3) * [0;0;1] .* 30;
    X2 = T2(1:3,1:3) * [1;0;0] .* 30;
    Y2 = T2(1:3,1:3) * [0;1;0] .* 15;
    Z2 = T2(1:3,1:3) * [0;0;1] .* 30;
    X3 = T3(1:3,1:3) * [1;0;0] .* 30;
    Y3 = T3(1:3,1:3) * [0;1;0] .* 15;
    Z3 = T3(1:3,1:3) * [0;0;1] .* 30;

    % plot the coordinate frames as vectors
    quiver3(J0(1),J0(2),J0(3),X0(1),X0(2),X0(3),'r');
    quiver3(J0(1),J0(2),J0(3),Y0(1),Y0(2),Y0(3),'g');
    quiver3(J0(1),J0(2),J0(3),Z0(1),Z0(2),Z0(3),'b');
    quiver3(J1(1),J1(2),J1(3),X1(1),X1(2),X1(3),'r');
    quiver3(J1(1),J1(2),J1(3),Y1(1),Y1(2),Y1(3),'g');
    quiver3(J1(1),J1(2),J1(3),Z1(1),Z1(2),Z1(3),'b');
    quiver3(J2(1),J2(2),J2(3),X2(1),X2(2),X2(3),'r');
    quiver3(J2(1),J2(2),J2(3),Y2(1),Y2(2),Y2(3),'g');
    quiver3(J2(1),J2(2),J2(3),Z2(1),Z2(2),Z2(3),'b');
    quiver3(J3(1),J3(2),J3(3),X3(1),X3(2),X3(3),'r');
    quiver3(J3(1),J3(2),J3(3),Y3(1),Y3(2),Y3(3),'g');
    quiver3(J3(1),J3(2),J3(3),Z3(1),Z3(2),Z3(3),'b');

    % set a limit of the 3D plot frame to better visualize the
    % stick model
    xlim([-600 600])
    ylim([-200 200])
    zlim([0 300])

    hold off
end