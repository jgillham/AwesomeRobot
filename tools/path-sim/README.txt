
***********************notes about the notation used in this program:************************************

1)  The suffix _R applied to coordinates means that coordinate is in a robot's frame
        _R coordinates are dependent upon the pose of the robot percieving them!
    The suffix _B means that coordinate is in the board's frame
        Some variables I do not bother to specify--for example, "pose" objects are ALWAYS in board frame
    The suffix _S means that it is in the screen frame
2)  The prefix SIM_ means that header or function is a simulator function, and will not
        be part of the robot's behavior
    The prefix BOT_ means that that header or function WILL be part of the robot's behavior
    The prefix GEN_ meas that header will be used by BOTH (no prefix also means this)
        general functions are not prefixed, however.
3)  Wire_in and Wire_out are prefixes used to describe variables that communicate between the simulated robot
        and the rest of the simulated world.  These prefixes are WI_ and WO_, since we want to communicate consisely.
4)  There are 2 kinds of robot in this simulation:  THE robot, which is the real robot, and the object Robot, of which
        the real robot's physical body is only one instance.   The others are hypobots, that is, hypotheses about where the
        robot is.







***************************The main structure of this program:******************************************

main.cpp:
    The globals:
        Globals are generally bad, so we try not to use them.  However, there are a hanful of paramaters, all related to
        the properties of the user interface, that are appropriate as globals.  So those are included.

    The initializer:
        This is where are public variables and objects are set.  It is divided into three sections:
            a) World objects:   we declare the physical objects of the world:
                an array of trees,          --- an array of rocks, an array of logs
                the realBot state,          --- the simulator uses this to generate sensor data
                the puckHere[] booleans     --- which pucks remain to be collected
            b) Wires:  how the simulated robot communicates with the simulated world (will be handled by an Arduino Mega):
                WO_rangefind                --- tells the rangefinders to rangefind
                WO_mastTheta                --- commands the mast servo to move the mast
                WO_wheelTheta1, 2, 3, 4     --- commands the steering servos to yaw the wheels
                WO_wheelOmega1, 2, 3, 4     --- commands the driving motors to roll the wheels at an angular velocity
                //A bunch of arm-related stuff, Simulator doesn't implement that yet

                WI_irRange1, 2, 3, 4        --- range data from Infrared triangulator sensors on mast
                WI_usRange1, 2, 3, 4        --- range data from Ultrasound sensors on mast
                WI_gyroX,Y,Z                --- gyrometer data about the X, Y, Z axes (robot frame, x is heading, right handed coords)
                WI_accelX,Y,Z               --- accelerometer data along the X, Y, Z axes (ditto)

            c) Robot objects:  Objects that exist in the robot's head:
                the percBot state,          --- short for "percieved" = the robot's best guess about its' position
                the desiredBot state        --- the state the robot WANTS to be in
                the deltaBot states         --- the difference between percieved state and desired states
                the hypoBot[] states,       --- the robot uses these to stencil its' P(x,y,theta)
                flags and states            --- lots of these, discussed in the "RobotLoop" section.


    The game loop:
        The game loop runs once per simulated millisecond.  It simulates updates in the environment and one pass through the
        robot's main ()loop.  It contains all the following (steps marked with :
            a) User input.  This is mostly a set of switch statements that poll an SDL event, which changes when the user puts in inputs.
            b) Advance the world.  This involves taking the v's of the all the robots and changing their poses by that amount.
            d) Robot sensors.  If any sensors have "take measurement" signals on their output wires, the corresponding input wires will
            now have signals on them.
            e) Robot main, named r_main().  The structure of the main loop is such that it can run as a while(1) on the real robot,
            or can run as a subroutine of the simulator loop.  This is accomplished with a system of "gates".
                1) Read sensor data from WI_s.
                2) RobotLoop: -- this is complicated and (obviously) crucial, so it's outlined in its own section below.
                3) Output motor signals to WO_s.
            f) Robot motors.  The WO's are used to update the robot's velocities.
            g) Draw.  Draw things to SDL_Surfaces, then blit the surfaces to the screen, then flip (show) the screen.

        Each pass through the loop looks at the
        the velocity and angular velocity of each robot and updates them accordingly,
        1a) It also runs through THE robot's main loop

***************************class state:******************************************

state.cpp/state.h:
    These files define and declare the class "state."

    attributes:
        float x, y, z, theta:  The pose of the robot.  Cartesian coords, origin is bottom left corner, measured in feet and degrees.
                                Theta = 0 is along positive x axis, positive theta is counterclockwise (looking down)
        float x_dot, y_dot, z_dot, theta_dot: the first time derivative of pose.
        bool isCollided:  turns true if collision detection returns positive.

        MANY MORE COMING!

***************************coordinate objects and functions:******************************************

pt_B:  a point on the board, cartesian coords, origin lower left, measured in feet
pt_R:  a point in the (polar or cartesian) frame of the robot.  x is heading (straight forward), y is due right,
            theta is heading, poisitve theta is counterclockwise (looking down)
pt_S:  a point on the screen, in pixels, origin is UPPER left corner

pt_S(pt_B)  good for drawing
pt_B(pt_S)  good for translating user input
pt_B(pt_R, bot)
pt_R(pt_B, bot)

instruction.h:
    getInstruction() is a very key function.
