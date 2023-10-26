function T = static3001(q, F)

    J = jacob3001(q);
    Jv = J(1:3,:);

    T = Jv' * F;
end