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