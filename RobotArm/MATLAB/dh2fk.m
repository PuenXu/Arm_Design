% takes in an n × 4 array corresponding to the n rows of the full DH parameter table
% then generates a corresponding symbolic 4 × 4 homogeneous transformation matrix
function T = dh2fk(parameters)

    numOfRows = size(parameters,1); % determine to number of rows of input
    
    T = eye(4); % create a 4x4 identity matrix to initialize T

    % calculate the overall transformation matrix
    for i = 1:numOfRows
        
        T = T * dh2mat(parameters(i,:));

    end
end