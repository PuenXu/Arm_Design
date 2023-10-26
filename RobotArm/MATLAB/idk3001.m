function w = idk3001(q, pdot)

    J = jacob3001(q);

    w = J \ pdot;
end