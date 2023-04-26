% Parameters
gamma = 1.4; % Ratio of specific heats
N = 1000; % Number of grid points
L = 1; % Length of the domain
dx = L/N; % Grid spacing
dt = 0.0001; % Time step
t_final = 0.2; % Final time

% Initial conditions
x = linspace(0, L, N);
rho = ones(1, N);
rho(x>0.5) = 0.125;
u = zeros(1, N);
p = ones(1, N);
p(x>0.5) = 0.1;
E = p/(gamma-1) + 0.5*rho.*u.^2;

% Godunov method
t = 0;
while t < t_final
    % Compute time step
    a = sqrt(gamma*p./rho);
    dt = 0.25*dx./(abs(u) + a);
    dt = min(dt);
    if t + dt > t_final
        dt = t_final - t;
    end
    
    % Compute fluxes
    f = zeros(3, N+1);
    for i = 1:N+1
        if i == 1
            f(:, i) = euler_flux(rho(1), u(1), p(1), gamma);
        elseif i == N+1
            f(:, i) = euler_flux(rho(end), u(end), p(end), gamma);
        else
            f(:, i) = riemann_solver(rho(i-1), u(i-1), p(i-1), rho(i), u(i), p(i), gamma);
        end
    end
    
    % Update solution
    rho = rho - dt/dx*(f(1, 2:end) - f(1, 1:end-1));
    u = u - dt/dx*(f(2, 2:end) - f(2, 1:end-1));
    E = E - dt/dx*(f(3, 2:end) - f(3, 1:end-1));
    p = (gamma-1)*(E - 0.5*rho.*u.^2);
    
    % Boundary conditions
    rho(1) = rho(2);
    rho(end) = rho(end-1);
    u(1) = -u(2);
    u(end) = -u(end-1);
    
    % Update time
    t = t + dt;
end

% Plot solution
figure;
plot(x, rho, 'b', 'LineWidth', 2);
xlabel('x');
ylabel('Density');
title('1D Compressible Euler Equations with a Shock Wave');
xlim([0 L]);

figure;
plot(x, u, 'b', 'LineWidth', 2);
xlabel('x');
ylabel('Velocity');
title('1D Compressible Euler Equations with a Shock Wave');
xlim([0 L]);

figure;
plot(x, p, 'b', 'LineWidth', 2);
xlabel('x');
ylabel('Pressure');
title('1D Compressible Euler Equations with a Shock Wave');
xlim([0 L]);

% Function to compute Euler fluxes
function f = euler_flux(rho, u, p, gamma)
    f = [rho*u; rho*u^2 + p; (p/(gamma-1) + 0.5*rho*u^2 + p)*u];
end

% Function to compute Riemann fluxes
function f = riemann_solver(rho_l, u_l, p_l, rho_r, u_r, p_r, gamma)
    % Compute left and right state variables
    c_l = sqrt(gamma*p_l/rho_l);
    c_r = sqrt(gamma*p_r/rho_r);
    rho_star = 0.5*(rho_l + rho_r) + 0.5*(u_l - u_r)/c_l/sqrt(2/gamma/(gamma-1)/rho_l + 2/gamma/(gamma-1)/rho_r);
    p_star = 0.5*(p_l + p_r) + 0.5*(u_l - u_r)*rho_star*c_l;
    if p_star < 0
        p_star = 0;
    end
    u_star = 0.5*(u_l + u_r) + 0.5*(p_l - p_r)/rho_star/c_l;
    
    % Compute left and right wave speeds
    s_l = u_star - c_l;
    s_r = u_star + c_r;
    
    % Compute Euler fluxes at left and right states
    f_l = euler_flux(rho_l, u_l, p_l, gamma);
    f_r = euler_flux(rho_r, u_r, p_r, gamma);

    % Compute total energy per unit volume at the right state
    E_r = p_r/(gamma-1) + 0.5*rho_r*u_r^2;
    E_l = p_l/(gamma-1) + 0.5*rho_l*u_l^2;

    % Compute numerical flux
    if s_l > 0
        f = euler_flux(rho_l, u_l, p_l, gamma);
    elseif s_r < 0
        f = euler_flux(rho_r, u_r, p_r, gamma);
    else
        f = zeros(3, 1);
        f(1) = (s_r*f_l(1) - s_l*f_r(1) + s_l*s_r*(rho_r - rho_l))/(s_r - s_l);
        f(2) = (s_r*f_l(2) - s_l*f_r(2) + s_l*s_r*(rho_r*u_r - rho_l*u_l))/(s_r - s_l) + (p_star - 0.5*(rho_l + rho_r)*(s_r - s_l))*0.5*(sign(s_l) + sign(s_r));
        f(3) = (s_r*f_l(3) - s_l*f_r(3) + s_l*s_r*(rho_r*E_r - rho_l*E_l))/(s_r - s_l) + (p_star*u_star - 0.5*(rho_l*u_l + rho_r*u_r)*(s_r - s_l))*0.5*(sign(s_l) + sign(s_r));
    end
end
