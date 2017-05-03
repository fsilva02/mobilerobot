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
#include <control_msg/control.h>

#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

using namespace std;

int main(int argc, char **argv)
{

	ros::init(argc, argv,"nardo_base");
	ros::NodeHandle nh;

	ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("nardo/cmd_vel", 100); 

  // impressão da mensagem inicial
  cout <<"                            Nodo de Teleoperação                                   " << endl
      <<"                                                                                   " << endl
      <<"Instruções:                                                                        " << endl
      <<"Para o controlo da velocidade usar teclas 'q' e 'z' para aumentar mais rápidamente;" << endl
      <<"Para o controlo da velocidade usar teclas 'w' e 'x' para aumentar mais devagar;    " << endl
      <<"Para o controlo da velocidade usar teclas 'e' e 'c' para diminuir mais rápidamente;" << endl
      <<"Para o controlo da velocidade usar teclas 'r' e 'v' para diminuir mais devagar;    " << endl
      <<"                                                                                   " << endl
      <<"Controlo posição:                                                                  " << endl
      <<"                       u i o                                                       " << endl
      <<"                       j k l                                                       " << endl
      <<"                       m , .                                                       " << endl
      <<"                                                                                   " << endl;

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
    if(ch == 'u')
		{
      msg.linear.x=vel_l;
      msg.angular.z=vel_w*(-1);
      //printw("angular velocity: %f \n",vel_w );
      pub.publish(msg);
		}
    else if(ch == 'i')
		{
      msg.linear.x=vel_l;
      msg.angular.z=0;
      //printw("angular velocity: %f\n",vel_w );
      pub.publish(msg);
		}
    else if(ch == 'o') 		{
			msg.linear.x=vel_l;
      msg.angular.z=vel_w;
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);

		}
    else if(ch == 'j')
		{
      msg.linear.x=0;
      msg.angular.z=vel_w*(-1);
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
		}
    else if(ch == 'k') //stop
    {
      msg.linear.x=0;
      msg.angular.z=0;
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
    }
    else if(ch == 'l')
    {
      msg.linear.x=vel_l*(-1);
      msg.angular.z=0;
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
    }
    else if(ch == 'm')
    {
      msg.linear.x=vel_l*(-1);
      msg.angular.z=vel_w;
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
    }
    else if(ch == ',')
    {
      msg.linear.x=vel_l*(-1);
      msg.angular.z=0;
      //printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
    }
    else if(ch == '.')
    {
      msg.linear.x=vel_l*(-1);
      msg.angular.z=0;
      printw("linear velocity: %f\n", vel_l );
      pub.publish(msg);
    }
    // controlo da velocidade linear
    else if( ch == 'q')
		{
      vel_l = vel_l + 0.1;
      printw("velovidade linear: %f\n", vel_l);
		}
    else if( ch == 'z')
		{
      vel_l = vel_l - 0.1;
      printw("linear velocity: %f\n", vel_l );
		}
    else if( ch == 'w')
		{
      vel_w = vel_w + 0.01;
      printw("angular velocity: %f\n", vel_w );
		}
    else if( ch == 'x')
		{
      vel_w = vel_w - 0.01;
      printw("angular velocity: %f\n", vel_w );
		}
    // controlo da velocidade angular
    else if( ch == 'e')
    {
      vel_w = vel_w + 0.01;
      printw("angular velocity: %f\n", vel_w );
    }
    else if( ch == 'c')
    {
      vel_w = vel_w - 0.01;
      printw("angular velocity: %f\n", vel_w );
    }
    else if( ch == 'r')
    {
      vel_w = vel_w + 0.1;
      printw("angular velocity: %f\n", vel_w );
    }
    else if( ch == 'v')
    {
      vel_w = vel_w - 0.1;
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
