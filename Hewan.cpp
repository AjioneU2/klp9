#define NULL 0
#define TORSO_HEIGHT 4.0
#define TORSO_RADIUS 1.50
#define UPPER_FRONT_HEIGHT 2.0
#define LOWER_FRONT_HEIGHT 0.10
#define LOWER_BACK_HEIGHT 0.10
#define UPPER_FRONT_RADIUS 0.5
#define LOWER_FRONT_RADIUS 0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0

#include <GL/glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


//set head, torso, and all the feet
void head();
void torso();
void left_upper_front();
void right_upper_front();
void left_upper_back();
void right_upper_back();



typedef float point[3];

typedef struct treenode{
 GLfloat m[16];
 void (*f)();
 struct treenode *sibling;
 struct treenode *child;
} treenode;

typedef treenode* t_ptr;

static GLfloat theta[11] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0};

static GLint acc = 1, acc1 = 1, acc2 = 1;

GLUquadricObj *t, *h, *luf, *llf, *ruf, *rlf, *llb, *rlb, *rub, *lub;

treenode torso_node, head_node, luf_node, ruf_node, llb_node, rlb_node, llf_node,
   rlf_node, rub_node, lub_node;

void TimerFunc(int value){
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void traverse(treenode * root){
 if(root==NULL) return ;
 glPushMatrix();
 glMultMatrixf(root->m);
 root->f();
 if(root->child!=NULL) traverse(root->child);
 glPopMatrix();
 if(root->sibling!=NULL)traverse(root->sibling);
}

void torso(){
 glPushMatrix();
 glColor3ub(139,90,43); //tan4
 glRotatef(-90.0, 0.0, 1.0, 0.0);
 gluSphere(t, TORSO_RADIUS, 10, 10);
 gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
 glTranslatef(0.0, 0.0, TORSO_HEIGHT );
 gluSphere(t, TORSO_RADIUS, 10, 10);
 glPopMatrix();
 //tail
 glPushMatrix();
 glColor3ub(139,90,43); //tan4
 glTranslatef(-5.70, 0.90, 0.0);
 glScalef(2.50, 0.5, 0.50);
 gluSphere(h, 0.5, 10, 10);
 glPopMatrix();
}

void head(){
 glPushMatrix();
 glTranslatef(-0.20, 4.0, 0.0);
 glPushMatrix();
 glTranslatef(1.80, -2.50, 0.0);
 glScalef(1.70, 1.0, 1.40);
 gluSphere(h, 1.0, 10, 10);
 glPopMatrix();
 
 //the move
 //torso
 glPushMatrix();
    glRotatef(theta[0], 0.0, 1.0, 0.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,torso_node.m);
 theta[0] += acc1;
 glPopMatrix();

 //head
 glPushMatrix();
    glRotatef(theta[1], 0.0, 1.0, 0.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,head_node.m);
 if(theta[1] > 20 || theta[1] < -60)
  acc = -acc;
 theta[1] += acc;
 glPopMatrix();

 //luf
 glPushMatrix();
    glRotatef(theta[3], 0.0, 0.0, 1.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,luf_node.m);
 if(theta[3] > 10 || theta[3] < -10)
  acc1 = -acc1;
 theta[3] += 2*acc1;
 glPopMatrix();
 //llf
 glPushMatrix();
    glRotatef(theta[4], 0.0, 1.0, 0.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,llf_node.m);
 if(theta[4] > 0 || theta[4] < -10)
  acc2 = -acc2;
 theta[4] += acc2;
 glPopMatrix();

 //lub
 glPushMatrix();
 glTranslatef(-4.0, 0.0, 0.0);
 glPushMatrix();
    glRotatef(theta[7], 0.0, 0.0, 1.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,lub_node.m);
 theta[7] += 2*acc1;
 glPopMatrix();
 glPopMatrix();
 //llb
 glPushMatrix();
 glTranslatef(-4.0, 0.0, 0.0);
 glPushMatrix();
    glRotatef(theta[8], 0.0, 0.0, 0.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,llb_node.m);
 theta[8] += acc2;
 glPopMatrix();
 glPopMatrix();

 //ruf
 glPushMatrix();
    glRotatef(theta[5], 0.0, 0.0, 1.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,ruf_node.m);
 theta[5] += 2*-acc1;
 glPopMatrix();
 //rlf
 glPushMatrix();
    glRotatef(theta[6], 0.0, 1.0, 0.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,rlf_node.m);
 theta[6] += -acc2;
 glPopMatrix();

 //rub
 glPushMatrix();
 glTranslatef(-4.0, 0.0, 0.0);
 glPushMatrix();
    glRotatef(theta[9], 0.0, 0.0, 1.0);
 glGetFloatv(GL_MODELVIEW_MATRIX,rub_node.m);
 theta[9] += 2*-acc1;
 glPopMatrix();
 glPopMatrix();
