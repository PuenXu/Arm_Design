% Takes 3x1 configuation q and 3x1 instantaneous joint velocities
% qDot and returns a 6x1 vector with task space linear and angular
% velocities
function pDot = fdk3001(q, qDot)

    J = jacob3001(q);
    pDot = J*qDot;

end