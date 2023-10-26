function A = dh2mat(parameters)
    
    % record the corresponding HD parameters
    theta = parameters(1,1) * pi / 180;
    d = parameters(1,2);
    a = parameters(1,3);
    alpha = parameters(1,4) * pi / 180;

    % hardcode the corresponding homogeneous transformation matrix
    A = [cos(theta),-sin(theta)*cos(alpha),sin(theta)*sin(alpha),a*cos(theta);
         sin(theta),cos(theta)*cos(alpha),-cos(theta)*sin(alpha),a*sin(theta);
         0,sin(alpha),cos(alpha),d;0,0,0,1];
end