/*
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:Haocheng ZHENG
 * ANDREW ID:haochenz
 * LAST UPDATE:9/17/2021
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 *
 */

#include "student.h"

/* Ignore this line until project 5 */
turtleMove studentTurtleStep( bool bumped )
{
    return(MOVE);
}


/* OK TO MODIFY BELOW THIS LINE */

//#define TIMEOUT 40    /* bigger number slows down simulation so you can see what's happening */
typedef int nums;
typedef bool check;
typedef enum state{move, stop}; //should turtle move or not
typedef enum orientation{right,down,left,up};//turtle orientation
typedef struct Position //struct for turtle position
{
    int fx1, fy1, fx2, fy2;
};


/*
 * this procedure takes the current turtle position and orientation and returns
 * true=submit changes, false=do not submit changes
 * Ground rule -- you are only allowed to call the helper functions "bumped(..)" and "atend(..)",
 * and NO other turtle methods or maze methods (no peeking at the maze!)
 */

// If right is free:
//     Turn right
// Else if right is occupied and straight is free:
//     Go Straight
// Else if right and straight are occupied:
//     Turn left 
// Else if left/right/straight are occupied or you crashed:
//     Turn 180 degrees






bool studentMoveTurtle( QPointF & pos_, int & nw_or )//nw_or is turtle orientation
{
    static state current_state;
    orientation turtle_ori;
    static check z, aend, bp;
    static nums wait_time; // wait_time is wait time for each movement.
    Position turtle_position;
    
    static int TIMEOUT = 2; //Timeout number
    turtle_ori = static_cast<orientation>(nw_or);

    if ( wait_time == 0 ){
        turtle_position.fx1 = pos_.x(); 
        turtle_position.fy1 = pos_.y();
        turtle_position.fx2 = pos_.x(); 
        turtle_position.fy2 = pos_.y();//get current turtle position

        switch (turtle_ori){ //check wall at turtle's orientation
            case right:
                turtle_position.fy2 += 1;
                break;
            case down:
                turtle_position.fx2 += 1;
                break;
            case left:
                turtle_position.fx2 += 1; 
                turtle_position.fy2 += 1;
                turtle_position.fx1 += 1;
                break;
            case up:
                turtle_position.fx2 += 1; 
                turtle_position.fy2 += 1;
                turtle_position.fy1 += 1;
                break;
            default:
                ROS_ERROR("check wall at turtle's orientation");
        }
        
        bp = bumped( turtle_position.fx1, turtle_position.fy1, turtle_position.fx2, turtle_position.fy2 );//check is there is a wall at turtle's orientation

        aend = atend( pos_.x(), pos_.y() ); // check if the turtle reaches destination
        
        switch (turtle_ori){ //decide turtle orientation
            case right:
                if ( current_state == move ){  
                    nw_or = down;
                    current_state = stop;
                }else if ( bp ){  
                    nw_or = up;
                    current_state = stop;
                }else {
                    current_state = move;
                }
                break;
            case down:
                if ( current_state == move ){
                    nw_or = left; 
                    current_state = stop;
                }else if ( bp ){ 
                    nw_or = right;
                    current_state = stop;
                }else {
                    current_state = move;
                }
                break;
            case left:
                if ( current_state == move ){  
                    nw_or = up;
                    current_state = stop;
                }else if ( bp ){
                    nw_or = down; 
                    current_state = stop;
                }else {
                    current_state = move;
                }
                break;
            case up:
                if ( current_state == move ){
                    nw_or = right;   
                    current_state = stop;
                }else if ( bp ){
                    nw_or = left;    
                    current_state = stop;
                }else {
                    current_state = move;
                }
                break;
            default:
                ROS_ERROR("decide turtle orientation");
        }

        ROS_INFO( "Orientation=%f  STATE=%f", nw_or, current_state );
        z = current_state == move;// when current_state is equal to 2, z = true, otherwise false
        
        if ( z == true && aend == false ){// if turtle can move, move
            switch (turtle_ori){ //move turtle
                case right:
                    pos_.setX( pos_.x() - 1 );
                    break;
                case down:
                    pos_.setY( pos_.y() - 1 );
                    break;
                case left:
                    pos_.setX( pos_.x() + 1 );
                    break;
                case up:
                    pos_.setY( pos_.y() + 1 );
                    break;
                default:
                    ROS_ERROR("move turtle");
            }
            z = false;
        }
    }
    if ( aend ){// reaches destination. stop moving
        return(false);
    }
    if ( wait_time == 0 ){
        wait_time = TIMEOUT;
    }
    else {
        wait_time -= 1;
    }
    if ( wait_time == TIMEOUT ){
        return(true);
    }
    return(false);
}
