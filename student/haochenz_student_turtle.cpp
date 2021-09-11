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

#define TIMEOUT 40    /* bigger number slows down simulation so you can see what's happening */
float	w; // w is wait time for each movement.
float 	current_state; 
float	fx1, fy1, fx2, fy2;
float	z, aend, bp;

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





bool studentMoveTurtle( QPointF & pos_, int & nw_or )//nw_or is turtle orientation, facing left: 2
{
	//ROS_INFO( "Turtle update Called  w=%f", w );
	
	
	if ( w == 0 ){
		ROS_INFO( "initial orentation=%f  STATE=%f", nw_or, current_state );
		fx1	= pos_.x(); fy1 = pos_.y();
		fx2	= pos_.x(); fy2 = pos_.y();//get current turtle position
		ROS_INFO( "Before: fx1=%f  fy1=%f fx2=%f fy2=%f", fx1, fy1,fx2,fy2 );
		
		if ( nw_or < 2 ){
			if ( nw_or == 0 ){
				fy2 += 1;
			}
			else {
				fx2 += 1;
			}
		}
		else{ 
			fx2 += 1; fy2 += 1;

			if ( nw_or == 2 ){
				fx1 += 1;
			}
			else {
				fy1 += 1
			};
		}
		ROS_INFO( "After: fx1=%f  fy1=%f fx2=%f fy2=%f", fx1, fy1,fx2,fy2 );

		ROS_INFO( "1: Orientation=%f  STATE=%f", nw_or, current_state );
		
		bp	= bumped( fx1, fy1, fx2, fy2 );
		aend	= atend( pos_.x(), pos_.y() ); // check if the turtle reaches destination
		
		if ( nw_or == 0 ){

			if ( current_state == 2 ){
				nw_or = 3;  
				current_state = 1;
			}else if ( bp ){
				nw_or = 1;  
				current_state = 0;
			}else {
				current_state = 2;
			}
			ROS_INFO( "2: Orientation=%f  STATE=%f", nw_or, current_state );
		}
		else if ( nw_or == 1 ){
			if ( current_state == 2 ){
				nw_or = 0; 
				current_state = 1;
			}else if ( bp ){
				nw_or = 2;  
				current_state = 0;
			}else {
				current_state = 2;
			}
			ROS_INFO( "3: Orientation=%f  STATE=%f", nw_or, current_state );
		}
		else if ( nw_or == 2 ){
			if ( current_state == 2 ){
				nw_or = 1;  
				current_state = 1;
			}else if ( bp ){
				nw_or = 3; 
				current_state = 0;
			}else {
				current_state = 2;
			}
			ROS_INFO( "4: Orientation=%f  STATE=%f", nw_or, current_state );
		}
		else if ( nw_or == 3 ){
			if ( current_state == 2 ){
				nw_or = 2;  
				current_state = 1;
			}else if ( bp ){
				nw_or = 0;  
				current_state = 0;
			}else {
				current_state = 2;
			}
			ROS_INFO( "5: Orientation=%f  STATE=%f", nw_or, current_state );
		}

		ROS_INFO( "6: Orientation=%f  STATE=%f", nw_or, current_state );
		z	= current_state == 2;// when current_state is equal to 2, z = true, otherwise false
		
		if ( z == true && aend == false ){
			if ( nw_or == 1 ){
				pos_.setY( pos_.y() - 1 );
			}
			if ( nw_or == 2 ){
				pos_.setX( pos_.x() + 1 );
			}
			if ( nw_or == 3 ){
				pos_.setY( pos_.y() + 1 );
			}
			if ( nw_or == 0 ){
				pos_.setX( pos_.x() - 1 );
			}
			z	= false;
		}
		ROS_INFO( "7: Orientation=%f  STATE=%f", nw_or, current_state );
	}
	if ( aend ){// reaches destination. stop moving
		return(false);
	}
	if ( w == 0 ){
		w = TIMEOUT;
	}
	else {
		w -= 1;
	}
	if ( w == TIMEOUT ){
		return(true);
	}
	return(false);
}