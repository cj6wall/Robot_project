//
//  main.cpp
//  Robot
//
//  Created by Kent Hu on 2017/5/9.
//  Copyright © 2017年 Kent Hu. All rights reserved.
//

#include <glut/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

float angle[10] = {};
float angleB[10] = {};
//pos已用了0,1,2
float posx[10] = {};
float posy[10] = {};
float posz[10] = {};
float angleForR[10] = {};
float angleForA[10] = {};
float timeclock = 0;
bool isIdle = true;
bool isSwingForward = false; //ForRun
bool isSwingForwardHand = false; //ForRun
bool isDown = true;
bool weapon = false;

void drawboby()
{
    glColor3f(0.5, 0.1, 0.5);
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslated(0, 0, -0.2);
            GLUquadricObj *p;
            p = gluNewQuadric();
            gluQuadricDrawStyle(p, GLU_LINE);
            gluCylinder(p,0.1, 0.1, 0.4, 500, 500); //身體
    glPopMatrix();
    
}

void drawhead()
{
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(0.26); //頭部
    
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0.06, 0.05, -0.1);
    glutSolidCube(0.07); //眼睛
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-0.06, 0.05, -0.1);
    glutSolidCube(0.07); //眼睛
    glPopMatrix();
   
    glPushMatrix();
    glColor3f(0, 1, 0);
    glScalef(0.3, 0.2, 0.2);
    glTranslatef(0, -0.3, -0.55);
    glutSolidCube(0.3); //嘴巴
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0.3, 0.3);
    glTranslatef(0, 0.12, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.1, 0.2, 10, 15); //帽子
    glPopMatrix();

}


void drawArm()
{
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glutSolidSphere(0.04, 20, 20); //關節點
            glPushMatrix();
                glColor3f(0.1, 0.5, 0.5);
                glScalef(0.4, 0.3, 0.3);
                glTranslated(0.19, 0, 0);
                glutSolidCube(0.3); //手臂
            glPopMatrix();
    glPopMatrix();
}

void drawleg()
{
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glutSolidSphere(0.04, 20, 20); //關節點
            glPushMatrix();
                glColor3f(0.2, 0.5, 0.7);
                glScalef(0.5, 0.2, 0.2);
                glTranslated(0.19, 0, 0);
                glutSolidCube(0.3); //腿
            glPopMatrix();
    glPopMatrix();

}

void drawweapon()
{
    glColor3f(1, 0, 1);
    glPushMatrix();
        GLUquadricObj *p;
        p = gluNewQuadric();
        gluQuadricDrawStyle(p, GLU_LINE);
        gluCylinder(p,0.02, 0.02, 0.2, 500, 500);
            glPushMatrix();
                glColor3f(1, 0, 0);
                glTranslatef(0, 0, 0.2);
                    GLUquadricObj *q;
                    q = gluNewQuadric();
                    gluQuadricDrawStyle(q, GLU_LINE);
                    gluCylinder(q,0.035, 0, 0.2, 500, 500);
                        glPushMatrix();
                            glColor3f(0, 0, 1);
                            glTranslatef(0, 0, -0.3);
                                GLUquadricObj *r;
                                r = gluNewQuadric();
                                gluQuadricDrawStyle(r, GLU_LINE);
                                gluCylinder(r,0.05, 0.02, 0.1, 500, 500);
                        glPopMatrix();
            glPopMatrix();
    glPopMatrix();
}

void display()
{
    glEnable(GL_DEPTH_TEST); //防止3D錯亂
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glMatrixMode(GL_MODELVIEW); //配reshape
    glLoadIdentity();
    gluLookAt(0, 1, -1.5,0, 0, 0,0, 1, 0); //（相機位置,看向物體哪裡,方向？？）

    ///**機器人本體
    glPushMatrix();
    glTranslatef(posx[0], posy[0], posz[0]); //全身移動
    glRotatef(angle[0], 0, 1, 0); //機器人左右轉
    glRotatef(angle[10], 1, 0, 0); //機器人上下轉
    glRotatef(angleForA[0], -1, 0, 0); //機器人就攻擊預備角度
    
    glPushMatrix(); //上半身
    glRotatef(angle[9], 1, 0, 0);
    
    glPushMatrix();
        glTranslatef(0, 0.33, 0);
        drawhead();
    glPopMatrix();
    
    drawboby(); //身體
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslated(0, -0.2, 0);
    glTranslatef(posx[2], posy[2], posz[2]);
    if(weapon)
        drawweapon(); //拿出武器
    glPopMatrix();


    
    glPushMatrix();
        glTranslatef(0.1, 0.08, 0);
    glRotatef(angleForR[0], 0, 0, 1); //跑步預備
    glRotatef(angleForR[5], 0, -1, 0); //跑步手擺動
    glRotatef(angle[5], 1, 0, 1); //右上手關節(X逆時針自轉,Z上下,Y往前,-Y往後)
    glRotatef(angleForA[5], 0, 1, 0);
        drawArm(); //右上手
            glPushMatrix();
                glTranslatef(0.15, 0, 0);
    glRotatef(angleForR[7], 0, -1, 0); //跑步手擺動
    glRotatef(angle[7], 0, 1, 1); //右下手關節
                drawArm(); //右下手
            glPopMatrix();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(180, 0, 1, 0);
        glTranslatef(0.1, 0.08, 0);
    glRotatef(angleForR[0], 0, 0, 1); //跑步預備
    glRotatef(angleForR[6], 0, 1, 0); //跑步手擺動
    glRotatef(angle[6], -1, 0, 1); //左上手關節(X順時針自轉,Z上下,-Y往前,Y往後)
    glRotatef(angleForA[6], 0, -1, 0);
        drawArm(); //左上手
            glPushMatrix();
                glTranslatef(0.15, 0, 0);
    glRotatef(angleForR[8], 0, 1, 0); //跑步手擺動
    glRotatef(angle[8], 0, -1, 1); //左下手關節
                drawArm(); //左下手
               glPopMatrix();
    glPopMatrix();
    
    glPopMatrix(); //上半身
    
    glPushMatrix(); //下半身
    glTranslatef(posx[1], posy[1], posz[1]);
    
    glPushMatrix();
        glRotatef(-90, 0, 0, 1);
        glTranslatef(0.2, -0.05, 0);
    glRotatef(angle[1], 0, 1, 0); // 右大腿關節
        drawleg();
            glPushMatrix();
                glTranslatef(0.19, 0, 0);
    glRotatef(angle[3], 0, 1, 0); //右小腿關節
                drawleg();
            glPopMatrix();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(-90, 0, 0, 1);
        glTranslatef(0.2, 0.05, 0);
    glRotatef(angle[2], 0, 1, 0); // 左大腿關節
        drawleg();
            glPushMatrix();
                glTranslatef(0.19, 0, 0);
    glRotatef(angle[4], 0, 1, 0); //左小腿關節
                drawleg();
            glPopMatrix();
    glPopMatrix();
    
    glPopMatrix(); //下半身
    
    glPopMatrix();
    ///**機器人本體

    glFlush();
    
    //angle[0] += 1;//機器人旋轉(自轉) 可配idle||motion
   
    
}

float oldx = 0;
void motion(int x,int y)
{
    angle[0] = x; //對著010轉Ｘ度『glRotatef(angle, 0, 1, 0)』
    angle[10] = y; //對著100轉Y度『glRotatef(angle, 1, 0, 0)』
    //angle += oldx - x/50;
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w/(float)h, 0.001, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
}

void SetLightSource()
{
    float light_ambient[]  = { 1.0, 1.0, 1.0, 1.0};
    float light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0};
    float light_specular[] = { 1.0, 1.0, 1.0, 1.0};
    
    glEnable(GL_COLOR_MATERIAL); //顏色還原
    
    glEnable(GL_LIGHTING);                                 //開燈
    glEnable(GL_LIGHT0);
    
    // 設定發光體的光源的特性
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);      //環境光(Ambient Light)
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //散射光(Diffuse Light)
    glLightfv( GL_LIGHT0, GL_SPECULAR,light_specular);     //反射光(Specular Light)
    
    float light_position[] = { -10, 20, 0}; //光源位置(左右 ,上下 ,前後)
    glLightfv( GL_LIGHT0, GL_POSITION,light_position);     //光的座標
    
}

void idle()
{
    timeclock = 0;
    angle[9]=0;
    posy[1]=0;
    posz[1]=0;
    
    //身體
    angleForA[0]=0;
    
    //腳
    angle[1]=0;
    angle[2]=0;
    angle[3]=0;
    angle[4]=0;
    angleForA[5]=0;
    angleForA[6]=0;
    
    //手
    angle[5]=0;
    angle[6]=0;
    angle[7]=0;
    angle[8]=0;
    angleForR[0]=0;
    angleForR[5]=0;
    angleForR[6]=0;
    angleForR[7]=0;
    angleForR[8]=0;
    
    posy[0]=0;
    
    //武器
    posz[2]=0;
    weapon = false;

}

void Run(int t)
{
    if(!isSwingForward){
        angle[2] = (angle[2] + 20);
        angle[1] = (angle[1] - 20);
        if(angle[2]>0){angle[4]=angle[4] - 5*1.2;angle[3]=angle[3] - 5*1.2;}
        else{angle[4]=angle[4] + 5*1.2;angle[3]=angle[3] + 5*1.2;}
    }
    else
    {
        angle[2] = (angle[2] - 20);
        angle[1] = (angle[1] + 20);
        if(angle[2]<0){angle[4]=angle[4] - 5*1.2;angle[3]=angle[3] - 5*1.2;}
        else{angle[4]=angle[4] + 5*1.2;angle[3]=angle[3] + 5*1.2;}    }
    if(angle[2]>25){
        isSwingForward = true;
    }
    if(angle[2]<-25){
        isSwingForward = false;
    }
    
    if(!isSwingForwardHand){
        angleForR[5] = (angleForR[5] + 20);
        angleForR[6] = (angleForR[6] - 20);
        if(angleForR[5]>0){angleForR[7]=angleForR[7] - 5*1.2;angleForR[8]=angleForR[8] - 5*1.2;}
        else{angleForR[7]=angleForR[7] + 5*1.2;angleForR[8]=angleForR[8] + 5*1.2;}
    }
    else
    {
        angleForR[5] = (angleForR[5] - 20);
        angleForR[6] = (angleForR[6] + 20);
        if(angleForR[5]<0){angleForR[7]=angleForR[7] - 5*1.2;angleForR[8]=angleForR[8] - 5*1.2;}
        else{angleForR[7]=angleForR[7] + 5*1.2;angleForR[8]=angleForR[8] + 5*1.2;}    }
    if(angleForR[5]>25){
        isSwingForwardHand = true;
    }
    if(angleForR[5]<-25){
        isSwingForwardHand = false;
    }

    display();
    glutPostRedisplay();
    if(!isIdle) glutTimerFunc(100, Run, 0);
}


void Jump(int t)
{
        if(timeclock>10){
        
        //上半身
        angle[9]+=5;
        posy[1]-=0.01;
        posz[1]-=0.015;
        //腳
        angle[1]-=5;
        angle[2]-=5;
        angle[3]+=5;
        angle[4]+=5;
        
        //手
        angle[7]-=5;
        angle[8]-=5;
        
        posy[0]+=0.15;
        

        
    }else{
        timeclock++;
        
        //上半身
        angle[9]-=5;
        posy[1]+=0.01;
        posz[1]+=0.015;
        
        
        //腳
        angle[1]+=8;
        angle[2]+=8;
        angle[3]-=10;
        angle[4]-=10;
        
        //手
        angle[5]-=5;
        angle[6]-=5;
        angle[7]+=5;
        angle[8]+=5;
        
        posy[0]-=0.05;
        
    }
    display();
    glutPostRedisplay();
    if(!isIdle) glutTimerFunc(100, Jump, 0);
  
}

void Bow(int t)
{
    if(!isDown)
    {
        angle[9]+=5;
        posy[1]-=0.01;
        posz[1]-=0.015;
        angle[6]+=3;
        angleForR[8]-=2;
        angleForR[5]+=5;
        angleForR[7]+=4;
        
    }else
    {
        
        //上半身
        angle[9]-=5;
        posy[1]+=0.01;
        posz[1]+=0.015;
        angle[6]-=3;
        angleForR[8]+=2;
        angleForR[5]-=5;
        angleForR[7]-=4;
        
    }
    if (angle[9]>0)
    {
        isDown = true; //執行else
    }
    if (angle[9]<-45)
    {
        isDown = false; //執行if
    }
    display();
    glutPostRedisplay();
    if(!isIdle) glutTimerFunc(100, Bow, 0);

}

void Attack(int t)
{
    
    posz[2]+=0.1;
    
    display();
    glutPostRedisplay();
    if(!isIdle) glutTimerFunc(100, Attack, 0);
} 


void main_menu_func(int value) //設立動作
{
    switch (value)
    {
        case 1:
            idle();
            angleForR[0]=-75;
            if(isIdle)glutTimerFunc(1000, Run, 0);
            isIdle = false;
            break;
        case 2:
            idle();
            if(isIdle)glutTimerFunc(1000, Jump, 0);
            isIdle = false;
            break;
        case 3:
            idle();
            if(isIdle)glutTimerFunc(1000, Bow, 0);
            isIdle = false;
            break;
        case 4:
            idle();
            weapon = true;
            angleForA[0] = 90; //攻擊預備位置
            angle[1] = 90; //右大腿
            angle[2] = 90; //左大腿
            angleForA[5] = 90;
            angleForA[6] = 90;
            if(isIdle)glutTimerFunc(1000, Attack, 0);
            isIdle = false;
            break;
        case 5:
            isIdle = true;
            idle();
            break;
    }

}


int main (int argc , char * argv[])
{
    glutInit(& argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robot Project1");
    glutMotionFunc(motion); //滑鼠拖曳
    glutReshapeFunc(reshape); //調整視窗及畫面
    
    int main_menu = glutCreateMenu(main_menu_func); //建立Menu
    glutSetMenu(main_menu);
    glutAddMenuEntry("Walk", 1); //Run
    glutAddMenuEntry("Jump", 2);
    glutAddMenuEntry("bow", 3);
    glutAddMenuEntry("Attack", 4);
    glutAddMenuEntry("Recover", 5); //idle
    glutAttachMenu(GLUT_RIGHT_BUTTON); //建出Menu
    
    //glutTimerFunc(100, timer, 0); //不可在這寫動作
    
    glutMotionFunc(motion);
    
    glutIdleFunc(display); //配機器人自轉
    glutDisplayFunc(display);
    
    SetLightSource();
    
    glutMainLoop();
    return 0;
    
}
