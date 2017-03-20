#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string>
#include <ncurses.h>
#include <unistd.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

int main(int argc, char **argv)
{

	ros::init(argc, argv,"nardo_base");
	ros::NodeHandle nh;

	ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("nardo/cmd_vel", 100); 

	int ch;
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	double vel_l = 0;
	double vel_w = 0;
	while (ch != 'q')
	{
		geometry_msgs::Twist msg;
		SLEEP( 10 );
		ch = getch();			/* If raw() hadn't been called
						 * we have to press enter before it
						 * gets to the program 		*/
		if(ch == KEY_RIGHT)
		{
			msg.linear.x=0;
			msg.angular.z=vel_w;
                        printw("angular velocity: %f \n",vel_w );
                        pub.publish(msg);
		}
		else if(ch == KEY_LEFT)
		{
			msg.linear.x=0;
			msg.angular.z=vel_w*(-1);
                        printw("angular velocity: %f\n",vel_w );
                        pub.publish(msg);
		}
		else if(ch == KEY_UP) // Up arrow key
		{
			msg.linear.x=vel_l;
			msg.angular.z=0;
                        printw("linear velocity: %f\n", vel_l );
                        pub.publish(msg);

		}
		else if(ch == KEY_DOWN)
		{
			msg.linear.x=vel_l*(-1);
			msg.angular.z=0;
                        printw("linear velocity: %f\n", vel_l );
                        pub.publish(msg);
		}
		else if(ch == KEY_BACKSPACE)
		{
			msg.linear.x=0;
			msg.angular.z=0;
                        printw("STOP");
                        pub.publish(msg);
		}
		else if( ch == 'w')
		{
                        vel_l = vel_l + 10;
                        printw("velovidade linear: %f\n", vel_l);
		}
		else if( ch == 'x')
		{
                        vel_l = vel_l - 10;
                        printw("linear velocity: %f\n", vel_l );
		}
		else if( ch == 'e')
		{
                        vel_w = vel_w + 10;
                        printw("angular velocity: %f\n", vel_w );
		}
		else if( ch == 'c')
		{
                        vel_w = vel_w - 10;
                        printw("angular velocity: %f\n", vel_w );
		}
		else
		{	printw("The pressed key is ");
			attron(A_BOLD);
			printw("%c\n", ch);
			attroff(A_BOLD);
		}
		//refresh();			/* Print it on to the real screen */
	}


	endwin();			/* End curses mode		  */
	exit(1);
	//return 0;
}
