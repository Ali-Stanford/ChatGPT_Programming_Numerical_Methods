import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
import numpy as np
import matplotlib.pyplot as plt

# Define the computational graph
graph = tf.Graph()
with graph.as_default():
    # Define the input tensors
    x = tf.placeholder(tf.float32, [None, 1], name='x')
    t = tf.placeholder(tf.float32, [None, 1], name='t')
    u = tf.placeholder(tf.float32, [None, 1], name='u')

    # Define the neural network architecture
    with tf.variable_scope('neural_net'):
        h1 = tf.layers.dense(tf.concat([x, t], axis=1), 50, activation=tf.nn.tanh)
        h2 = tf.layers.dense(h1, 50, activation=tf.nn.tanh)
        h3 = tf.layers.dense(h2, 50, activation=tf.nn.tanh)
        pred = tf.layers.dense(h3, 1, activation=None, name='pred')

    # Define the loss function
    with tf.variable_scope('loss'):
        # Define the PDE residual
        u_x, u_t = tf.gradients(pred, [x, t])
        u_xx = tf.gradients(u_x, [x])
        f = u_t - u_xx - tf.cos(x)*(tf.cos(t)-tf.sin(t))

        # Define the boundary conditions
        bc_left = tf.reduce_mean(tf.square(pred[:, 0] - u[:, 0]))
        bc_right = tf.reduce_mean(tf.square(pred[:, -1] - u[:, -1]))

        # Define the total loss
        loss = bc_left + bc_right + tf.reduce_mean(tf.square(f))

    # Define the optimizer
    with tf.variable_scope('optimizer'):
        optimizer = tf.train.AdamOptimizer().minimize(loss)

# Define the exact solution
def exact_solution(x, t):
    return np.cos(x)*np.cos(t) 

# Define the initial and boundary conditions
def initial_condition(x,t):
    return np.cos(x)*np.cos(t) 

def boundary_condition(x,t):
    return np.cos(x)*np.cos(t)

# Train the neural network
with tf.Session(graph=graph) as sess:
    sess.run(tf.global_variables_initializer())

    # Generate some training data
    x_train =  np.random.uniform(-1, 1, (5000, 1)) 
    t_train =  np.random.uniform(0, 1, (5000, 1)) 
    u_train = exact_solution(x_train, t_train)

    # Set the initial and boundary conditions
    u_train[:, 0] = initial_condition(x_train[:, 0], t_train[:, 0])
    u_train[:, -1] = boundary_condition(x_train[:, 0] , t_train[:, 0])

    # Train the neural network
    for i in range(1000):
        _, loss_val = sess.run([optimizer, loss], feed_dict={x: x_train, t: t_train, u: u_train})

        if i % 100 == 0:
            print('Step {}: loss = {}'.format(i, loss_val))

    # Evaluate the neural network on the test data  
    u_pred_val = sess.run(pred, feed_dict={x: x_train, t: t_train})

    # Print the mean squared error
    mse = np.mean(np.square(u_train - u_pred_val))
    print('Mean squared error: {}'.format(mse))

    plt.figure(figsize=(6, 6))
    plt.scatter(x_train, t_train, 0.1, color='blue', label='Training points')
    plt.xlabel('x')
    plt.ylabel('t')
    plt.title('Location of training points')
    plt.show()

    # Define the grid
    x = np.linspace(-1, 1, 100)
    t = np.linspace(0, 1, 100)
    X, T = np.meshgrid(x, t)

    # Compute the exact solution on the grid
    U = exact_solution(X, T)

    # Plot the contour of the solution
    plt.contourf(X, T, U,cmap='jet')
    plt.colorbar()
    plt.xlabel('x')
    plt.ylabel('t')
    plt.title('Exact Solution')
    plt.show()

    # Plot the contour of the prediction
    plt.scatter(x_train, t_train, 1.0, u_pred_val[:,0], cmap='jet')
    cbar= plt.colorbar()
    plt.xlabel('x')
    plt.ylabel('t')
    plt.title('Predicted Solution')
    plt.show()
