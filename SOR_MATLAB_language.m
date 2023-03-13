% Successive over-relaxation (SOR) method for solving a linear system of equations
% Ax = b
% Example: solve 4x1 + x2 + x3 = 1, x1 + 4x2 + x3 = 2, x1 + x2 + 4x3 = 3
% using SOR method with omega = 1.5 and tolerance = 1e-6

% Set up the system of equations
A = [4 1 1; 1 4 1; 1 1 4];
b = [1; 2; 3];

% Set up initial guess
x = [0; 0; 0];

% Set up relaxation parameter and tolerance
omega = 1.5;
tol = 1e-6;

% Set up maximum number of iterations
max_iter = 1000;

% Solve the system of equations using SOR method
for iter_count = 1:max_iter
    old_x = x;
    for i = 1:length(x)
        sigma = 0;
        for j = 1:length(x)
            if j ~= i
                sigma = sigma + A(i,j)*x(j);
            end
        end
        x(i) = (1 - omega)*x(i) + (omega/A(i,i))*(b(i) - sigma);
    end
    residual = norm(b - A*x);
    if residual < tol
        break
    end
end

% Display the solution and number of iterations
disp(['Solution:']);
disp(x);
disp(['Number of iterations: ' num2str(iter_count)]);
