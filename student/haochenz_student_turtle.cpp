/*
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:Haocheng ZHENG
 * ANDREW ID:haochenz
 * LAST UPDATE:9/10/2021
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
typedef struct Position //struct for turtle position
{
    int fx1, fy1, fx2, fy2;
};

state current_state;
Position turtle_position;

check z, aend, bp;
nums wait_time; // wait_time is wait time for each movement.
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
    static int TIMEOUT = 40; //Timeout number
    

    if ( wait_time == 0 ){
        turtle_position.fx1 = pos_.x(); 
        turtle_position.fy1 = pos_.y();
        turtle_position.fx2 = pos_.x(); 
        turtle_position.fy2 = pos_.y();//get current turtle position
                
        // if ( nw_or < 2 ){// check wall at turtle's orientation
        //     if ( nw_or == 0 ){
        //         turtle_position.fy2 += 1;
        //     }
        //     else {
        //         turtle_position.fx2 += 1;
        //     }
        // }
        // else{ 
        //     turtle_position.fx2 += 1; 
        //     turtle_position.fy2 += 1;
        //     if ( nw_or == 2 ){
        //         turtle_position.fx1 += 1;
        //     }
        //     else {
        //         turtle_position.fy1 += 1;
        //     }
        // }

        switch (nw_or)
        {
        case 0:
            turtle_position.fy2 += 1;
            break;
        case 1:
            turtle_position.fx2 += 1;
            break;
        case 2:
            turtle_position.fx2 += 1; 
            turtle_position.fy2 += 1;
            turtle_position.fx1 += 1;
            break;
        case 3:
            turtle_position.fx2 += 1; 
            turtle_position.fy2 += 1;
            turtle_position.fy1 += 1;
            break;
        default:
            ROS_ERROR("check wall at turtle's orientation")
        }
        
        bp = bumped( turtle_position.fx1, turtle_position.fy1, turtle_position.fx2, turtle_position.fy2 );//check is there is a wall at turtle's orientation

        aend = atend( pos_.x(), pos_.y() ); // check if the turtle reaches destination
        
        if ( nw_or == 0 ){
            if ( current_state == move ){  
                nw_or = 1;
                current_state = stop;
            }else if ( bp ){  
                nw_or = 3;
                current_state = stop;
            }else {
                current_state = move;
            }
        }
        else if ( nw_or == 1 ){
            if ( current_state == move ){
                nw_or = 2; 
                current_state = stop;
            }else if ( bp ){ 
                nw_or = 0;
                current_state = stop;
            }else {
                current_state = move;
            }
        }
        else if ( nw_or == 2 ){
            if ( current_state == move ){  
                nw_or = 3;
                current_state = stop;
            }else if ( bp ){
                nw_or = 1; 
                current_state = stop;
            }else {
                current_state = move;
            }
        }
        else if ( nw_or == 3 ){
            if ( current_state == move ){
                nw_or = 0;   
                current_state = stop;
            }else if ( bp ){
                nw_or = 2;    
                current_state = stop;
            }else {
                current_state = move;
            }    
        }

        ROS_INFO( "Orientation=%f  STATE=%f", nw_or, current_state );
        z = current_state == move;// when current_state is equal to 2, z = true, otherwise false
        
        if ( z == true && aend == false ){// if turtle can move, move
            if ( nw_or == 1 ){//move down
                pos_.setY( pos_.y() - 1 );
            }
            if ( nw_or == 2 ){//move left
                pos_.setX( pos_.x() + 1 );
            }
            if ( nw_or == 3 ){//move up
                pos_.setY( pos_.y() + 1 );
            }
            if ( nw_or == 0 ){//move right
                pos_.setX( pos_.x() - 1 );
            }
            z    = false;
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