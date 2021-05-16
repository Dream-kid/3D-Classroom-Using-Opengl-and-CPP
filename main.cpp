#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
const int width = 700;
const int height = 700;
float flw=0;
GLfloat eyeX = -214;
GLfloat eyeY = 5;
GLfloat eyeZ = -518;
int score=0;
GLfloat centerX = -288;
GLfloat centerY = 0;
GLfloat centerZ = 28;
double angle = 0 ;
bool l_on1 = true;
bool l_on2 = true;
bool l_on3 = true;
bool l_on4 = false;
float rot = -12;
float stop=0;
float door_angle=.5;
float l_height =0;
float spt_cutoff = 0;
unsigned int ID;
float fowd=0;
float lef=0;
bool left_turn=1;
vector<int>v;
float check1=-300;
float check2=-300;
float fire1=0;
bool fire2=0;
float a=-15,b=1,c=-155;
float ok=0;
int cnt_dwn=0;
bool mark11=0;
float add_lef=0;
float rop_inc=8;
float rop_inc1=8;
float rop_inc_bool=0;
float rop_inc_bool1=0;
bool bridge_j=0;
bool arr[10];
float l_val=.1;
int bridge_val=0;
bool is_start=1;
void reset()
{
    memset(arr,0,sizeof(arr));
    bridge_val=0;
    eyeX = -214;
    eyeY = 5;
    eyeZ = -518;

    centerX = -288;
    centerY = 0;
    centerZ = 28;

    stop=1;
    door_angle=.5;
    l_height =0;
    spt_cutoff = 0;

    fowd=0;
    lef=0;

    check1=-300;
    check2=-300;
    fire1=0;
    fire2=0;
    a=-15,b=1,c=-155;
    ok=0;
    cnt_dwn=0;
    mark11=0;
    add_lef=0;
    rop_inc=8;
    rop_inc1=8;
    rop_inc_bool=0;
    rop_inc_bool1=0;
    bridge_j=0;

    l_val=.1;
}
static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {3,1,5,7},  //front
    {6,4,0,2},  //back
    {2,3,7,6},  //top
    {1,0,4,5},  //bottom
    {7,5,4,6},  //right
    {2,0,1,3}   //left
};


void cube(float R=0.5, float G=0.5, float B=0.5, int type=0, float val=1,bool player=0)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {1,0,0,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);
    if(type==1)
    {

        // if(l_on1)
        glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        //  else
        //     glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    }
    else if(type==2)
    {
        if(l_on3)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else
        glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    if(!player)
    {
        glBegin(GL_QUADS);
        for (GLint i = 0; i <6; i++)
        {
            getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                        v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                        v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);
            glTexCoord2f(0,val);
            glVertex3fv(&v_cube[c_ind[i][0]][0]);
            glTexCoord2f(0,0);
            glVertex3fv(&v_cube[c_ind[i][1]][0]);
            glTexCoord2f(val,0);
            glVertex3fv(&v_cube[c_ind[i][2]][0]);
            glTexCoord2f(val,val);
            glVertex3fv(&v_cube[c_ind[i][3]][0]);
        }
        glEnd();
    }
}
class BmpLoader
{
public:
    unsigned char* textureData;
    int iWidth, iHeight;

    BmpLoader(const char*);
    ~BmpLoader();

private:
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
};

BmpLoader::BmpLoader(const char* filename)
{
    FILE *file=0;
    file=fopen(filename, "rb");
    if(!file)
        cout<<"File not found"<<endl;
    fread(&bfh, sizeof(BITMAPFILEHEADER),1,file);
    if(bfh.bfType != 0x4D42)
        cout<<"Not a valid bitmap"<<endl;
    fread(&bih, sizeof(BITMAPINFOHEADER),1,file);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;
    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(textureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for(int i=0; i<bih.biSizeImage; i+=3)
    {
        temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;

    }

    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}

BmpLoader::~BmpLoader()
{
    delete [] textureData;
}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


static void res(int width, int height)
{
    glViewport(0, 0, width, height);
}

void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}


void flr()
{
    glEnable(GL_TEXTURE_2D);
    if(left_turn)
        glBindTexture(GL_TEXTURE_2D,v[3]);
    else
        glBindTexture(GL_TEXTURE_2D,v[10]);

    glPushMatrix();


    glTranslatef(0,-0.5,-80);
    glScalef(220,1,220);
    glTranslatef(-0.5,-1,-0.5);
    cube(1,1,1,0,30);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void wall1()
{
    glEnable(GL_TEXTURE_2D);
    if(left_turn)
        glBindTexture(GL_TEXTURE_2D,v[0]);
    else
        glBindTexture(GL_TEXTURE_2D,v[12]);

    glPushMatrix();

//    glTranslatef(0,-0.5,0);
    glScalef(1,160,160);
    glTranslatef(-30,0,-1);
    cube(1,1,1,0,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void wall2()
{
    glEnable(GL_TEXTURE_2D);
    if(left_turn)
        glBindTexture(GL_TEXTURE_2D,v[0]);
    else
        glBindTexture(GL_TEXTURE_2D,v[12]);
    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(1,160,160);
    glTranslatef(29,0,-1);
    cube(1,1,1,0,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}




void headwall()
{
    glEnable(GL_TEXTURE_2D);
    if(left_turn)
        glBindTexture(GL_TEXTURE_2D,v[2]);
    else
        glBindTexture(GL_TEXTURE_2D,v[11]);
    glPushMatrix();

//    glTranslatef(0,-0.5,0);

    glTranslatef(0,-0.5,-80);
    glScalef(300,1,240);
    glTranslatef(-0.5,19,-.5);
    cube(0.690, 0.769, 0.871,0,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

float al1,dl1,sl1;
float al2,dl2,sl2;
float al3,dl3,sl3;
void light1(float a,float b,float c)
{
    glEnable(GL_LIGHT0);

    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.3+al1, 0.3+al1, .3+al1, 1.0};
    GLfloat l_dif[] =  {0.3+al1, 0.3+al1, .3+al1, 1.0};
    GLfloat l_spec[] = {0.3+al1, 0.3+al1, .3+al1, 1.0};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on1)
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);


}

void light2(float a,float b,float c)
{
    glEnable(GL_LIGHT2);
    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.3+al2, 0.3+al2, 0.3+al2, 1.0};
    GLfloat l_dif[] = {.6+dl2,.6+dl2,.6+dl2,1};
    GLfloat l_spec[] = {5+sl2,5+sl2,5+sl2,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on3)
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT2, GL_POSITION, l_pos);
    // GLfloat l_spt[] = {0,-1,0,1};
//    GLfloat spt_ct[] = {66};
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l_spt);
//    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);


}
void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.17,1.1,.75);     //Specify the coordinates for the right eye
    glRotatef(-45,0,0,1);
    glScalef(.9,.7,.7);            //Specify the size of the right eye
    cube(1.0,1.0,1.0,0,1,1);       //Specify the color of the eye
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.75);     //Specify the position for the left eye
    glRotatef(45,0,0,1);
    glScalef(.9,.7,.7);
    cube(1.0,1.0,1.0,0,1,1);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void legleft()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);     //Specify the position for the left leg
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void legright()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);     //Specify the position for the right leg
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void armleft()
{
    glPushMatrix();
    glTranslatef(-.82,0,.1);     //Specify the position for the left arm
    glRotatef(90,0,1,0);
    glRotatef(-50,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}

void armright()
{
    glPushMatrix();
    glTranslatef(.82,0,.1);      //Specify the position for the right arm
    glRotatef(90,0,1,0);
    glRotatef(-130,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}

void handleft()
{
    glPushMatrix();
    glTranslatef(.82,0,.1);     //Specify the position for the left hand
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
void handright()
{
    glPushMatrix();
    glTranslatef(-.82,0,.1);    //Specify the position for the right hand
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0,.78,.74);
    glScalef(.4,.4,.1);
    cube(0.0,0.0,0.0,0,1,1);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void teeth()
{
    glPushMatrix();
    cube(1.0,1.0,1.0,0,1,1);
    glTranslatef(-.08,.72,.76);
    glTranslatef(.055,0,.005 );
    glutSolidCube(.035);
    glTranslatef(.055,0,0 );
    glutSolidCube(.035);
    glPopMatrix();
}
void eyebrowleft()
{
    glPushMatrix();
    glTranslatef(-.3,1.5,.97);;
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
    cube(0.0,0.0,0.0,0,1,1);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void eyebrowright()
{
    glPushMatrix();
    glTranslatef(.3,1.5,.97);
    glRotatef(270,0,1,0);
    glRotatef(45,1,0,0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void neckring()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}



void head()
{
    GLUquadric *quad;
quad = gluNewQuadric();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[17]);
    glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9,.9,.9 );
   cube(1,1,1,0,1,1);
  gluQuadricTexture(quad,1);
    gluSphere(quad,1,100,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
float k=0;
void spin()
{
    angle +=k;
    k+=.01;
    if (angle >= 360)
        angle = 0;

        }
double a4=2;
double b4=1;
double c4= 10;
void fan()
{
    //fan stand

    float length = 10;
    float width = 0.3;
    glPushMatrix();
    glTranslatef(.4,-3+spt_cutoff+1.2,stop-.2);
      glPushMatrix();
     // glRotatef(l_height,0,1,0);
    glScalef(.1,.3,.1);
    glPushMatrix();
    glTranslatef(1,length/2,-4);
    glScalef(width,length,width);
    glTranslatef(-20,0,20);
    cube(0.4,0.4,0.1);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,.1,1);
    glTranslatef(-5,150,2);
    cube(1, 1, 1);            // Set color as glColor3f(R,G,B)
    glRotatef(angle, 0, 0, 1);
    glRecti(-a4, -a4, a4, a4);
    cube(1, 0, 0);
    glRecti(-b4, a4, b4, c4);
    glRecti(-c4, -b4, -a4, b4);
    glRecti(-b4, -c4, b4, -a4);
    glRecti(a4, -b4, c4, b4);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    cout<<l_height<<" "<<spt_cutoff<<" "<<stop<<endl;
}

void footleft()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);
    glScalef(1.5,.3,1.5);
    cube(0.0,0.0,0.0,0,1,1);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void footright()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);
    glScalef(1.5,.3,1.5);
    cube(0.0,0.0,0.0,0,1,1);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0,-.2,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluDisk(gluNewQuadric(),0,.8,30,30);
    glPopMatrix();
}

void BellyCoat()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluCylinder(gluNewQuadric(),.6,.8,1,100,100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1,.4,.65);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void middlebutton()
{
    glPushMatrix()  ;
    glTranslatef(-.1,.15,.7);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void bottombutton()
{
    glPushMatrix();
    glTranslatef(-.1,-.1,.75);
    glScalef(1.9,1.9,1.9);
    cube(0.0,0.0,0.0,0,1,1);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}


void walloff()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[0]);


    //cout<<spt_cutoff<<endl;

    glPushMatrix();
    glScalef(20,20,60);
    // glRotatef(,0,1,0);
    glTranslatef(11-13.45,0,-0.4+.6);
    cube(1,1,1,2);
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[4]);
    //door
    glPushMatrix();
    glScalef(20,20,10);
    glTranslatef(11-13.45+.1+3.7,0,-0.4+.6-.2-1.1);
    // glRotatef(,0,1,0);
    cube(1,1,1);
    glPopMatrix();


    //back wall
    glEnable(GL_TEXTURE_2D);
    if(left_turn)
        glBindTexture(GL_TEXTURE_2D,v[5]);
    else
        glBindTexture(GL_TEXTURE_2D,v[14]);

    glPushMatrix();
    glScalef(68,20,20);
    // glRotatef(,0,1,0);
    glTranslatef(3.11-3.599-.05,0,.9+.05-.9);
    cube(1,1,1-left_turn,0,1);
    if(fire1<=15&&!fire2)
        fire1+=.1;
    else
        fire1-=.1,fire2=1;
    if(fire1<=-15)
        fire2=0;

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //cout<<spt_cutoff<<" "<<l_height<<endl;
}


void wall()
{
    flr();
    wall1();
    wall2();
    headwall();
    walloff();
}


float window_val=1;
void window_light(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT3);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {.5* window_val, .5* window_val, .5* window_val, 1.0};
    GLfloat l_dif[] = {1* window_val,1* window_val,1* window_val,1};
    GLfloat l_spec[] = {1* window_val,1* window_val,1* window_val,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on4)
        glLightfv(GL_LIGHT3, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT3, GL_AMBIENT, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT3, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT3, GL_DIFFUSE, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT3, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT3, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT3, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {84};
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spt_ct);

}



int life=3;
bool over=0;

void game_over()
{
    life--;
    if(life==0)
    {
        over=1;
    }
    reset();
}
void spot_light4(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT5);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1+al3, 1+al3, 1+al3, 1.0};
    GLfloat l_dif[] = {1+dl3,1+dl3,1+dl3,1};
    GLfloat l_spec[] = {1+sl3,1+sl3,1+sl3,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on4)
        glLightfv(GL_LIGHT5, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT5, GL_AMBIENT, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT5, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT5, GL_DIFFUSE, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT5, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT5, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT5, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {30};
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT5, GL_SPOT_CUTOFF, spt_ct);

}


void spot_light3(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT4);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1+al3, 1+al3, 1+al3, 1.0};
    GLfloat l_dif[] = {1+dl3,1+dl3,1+dl3,1};
    GLfloat l_spec[] = {1+sl3,1+sl3,1+sl3,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on3)
        glLightfv(GL_LIGHT4, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT4, GL_AMBIENT, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT4, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT4, GL_DIFFUSE, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT4, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT4, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT4, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {30};
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, spt_ct);

}

int timer;
int a1=1,b1=0,c1=0;
void swoard()
{
    timer++;

    glPushMatrix();
    glTranslatef(0-1,.78-1.7,.74-.6);
    glScalef(.1,4,.1);

    if(timer%50==0)
    {
        a1 = rand() % 2;
        b1 = rand() % 2;
        c1 = rand() % 2;
    }
    cube(a1,b1,c1);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0-1+1.9,.78-1.7,.74-.6);
    glScalef(.1,4,.1);
    cube(c1,a1,b1);

    glPopMatrix();
    // cout<<flw<<" "<<spt_cutoff<<" "<<stop<<" "<<l_height<<endl;
}
void player()
{
   fan();
    swoard();
    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
    cube(0.0,1.0,0.0,0,1,1);
    neckring();
    cube(50/255.0,40/255.0,60/255.0,0,1,1);
    legright();
    legleft();
    cube(255/255.0,90/255.0,0,0,1,1);
    armleft();
    armright();
    BellyCoat();
    cube(0,185/255.0,0,0,1,1);
    handleft();
    handright();
    mouth();
    teeth();
    cube(255/255.0,222/255.0,173/255.0,0,1,1);
    head();
    cube(0.0,0.0,0.0,0,1,1);
    footleft();
    footright();
    topbutton();
    middlebutton();
    bottombutton();
    pupilleft();
    pupilright();


}

void fire()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[6]);
    glPushMatrix();
    glTranslatef(-45+fire1,-1.5,-155+45);
    glScalef(85,1.5,6);
    cube(1,1,0,0,3);
//cout<<spt_cutoff<<" "<<l_height<<endl;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-45+fire1,-1.5,-155+85);
    glScalef(85,1.5,6);
    cube(1,1,0,0,3);
//cout<<spt_cutoff<<" "<<l_height<<endl;
    glPopMatrix();


    if(c>=-109&&c<=-108.5&&b==1)
    {
        game_over();
    }

    if(c>=-69&&c<=-68.5&&b==1)
    {
        game_over();
    }
//cout<<a<<" "<<c<<endl;
    glDisable(GL_TEXTURE_2D);
}

void point()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[7]);
    glPushMatrix();
    glTranslatef(-15,3,-155+25);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    if(c<=-129&&c>=-131&&add_lef<=-2)
    {
        if(!arr[0])
            score++,arr[0]=1;
        // cout<<"point"<<endl;
    }
    //cout<<add_lef<<" "<<c<<endl;
//cout<<spt_cutoff<<" "<<l_height<<endl;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,3,-155+70);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2,3,-155+64);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    if(c<=-84&&c>=-87&&add_lef>=2)
    {
        if(!arr[1])
            score++,arr[1]=1;
        // cout<<"point1"<<endl;
    }
    if(c<=-78&&c>=-81&&add_lef>=2)
    {
        if(!arr[2])
            score++,arr[2]=1;
        // cout<<"point2"<<endl;
    }
    //cout<<add_lef<<" "<<c<<endl;
//cout<<spt_cutoff<<" "<<l_height<<endl;
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void point1()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[7]);
    glPushMatrix();
    glTranslatef(-10,3,-155+25);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    if(c<=-129&&c>=-131&&add_lef>=1)
    {
        //  cout<<"point"<<endl;
        if(!arr[3])
            score++,arr[3]=1;
    }

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,3,-155+50);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    if(c<=-104&&c>=-106&&add_lef<=-3)
    {
        if(!arr[4])
            score++,arr[4]=1;
        // cout<<"point23"<<endl;
    }

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,7,-155+74);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
//cout<<spt_cutoff<<" "<<l_height<<endl;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,7,-155+84);
    glRotatef(45,0,1,0);
    glScalef(2,2,1);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cout<<add_lef<<endl;

    if(c>=-81&&c<=-78&&add_lef>=0)
    {
        if(!arr[5])
            score++,arr[5]=1;
        //   cout<<"point2"<<endl;
    }
    if(c>=-71&&c<=-68&&add_lef>=0)
    {
        if(!arr[6])
            score++,arr[6]=1;
        //cout<<"point3"<<endl;
    }
    //cout
}
void design()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[9]);
    for(int i=0; i<=95; i+=15)
    {
        glPushMatrix();
        glTranslatef(27,4,-155+25+i);
        //glRotatef(-29.9,0,1,0);
        glScalef(1,8,4);
        cube(1,1,1);
        //cout<<add_lef<<" "<<c<<endl;
//cout<<spt_cutoff<<" "<<l_height<<endl;
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D,v[8]);
    for(int i=0; i<=115; i+=25)
    {
        glPushMatrix();
        glTranslatef(-30,0,-155+25+i);
        //glRotatef(-25,0,1,0);
        glScalef(4,15,4);
        cube(1,1,1);
        //cout<<add_lef<<" "<<c<<endl;
//cout<<spt_cutoff<<" "<<l_height<<endl;
        glPopMatrix();
    }

    glBindTexture(GL_TEXTURE_2D,v[14]);
    for(int i=0; i<=115; i+=25)
    {
        glPushMatrix();
        glTranslatef(-30,0,-155+25+i-.1);
        //glRotatef(-25,0,1,0);
        glScalef(4,15,.1);
        cube(1,1,1);
        //cout<<add_lef<<" "<<c<<endl;
//cout<<spt_cutoff<<" "<<l_height<<endl;
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}

void rope()
{

    //laser1
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,v[14]);
    cube(1,0,0,0,1,1);
    glLineWidth(12);
    glPushMatrix();
    glTranslatef(-25,-1.5,-155+45);
    glBegin(GL_LINES);
    glVertex2f(104-93,167-146);

    glVertex2f(1+rop_inc+13, 7-43);
    if(rop_inc_bool&&rop_inc<=29&&rop_inc>=12)
        rop_inc-=.1;
    else if(rop_inc<28)
    {
        rop_inc_bool=0;
        rop_inc+=.1;

    }
    else
        rop_inc_bool=1;

    glEnd();

    if(c>=-112 && c<=-108)
    {
        if(add_lef>-.8)
        {
            game_over();
        }
    }
    glPopMatrix();

//laser

    glPushMatrix();
    glTranslatef(-25-1-2,-1.5,-155+45-12);
    //
    glBegin(GL_LINES);
    glVertex2f(104-93,167-146);

    glVertex2f(1+rop_inc1+13, 7-43);
    if(rop_inc_bool1&&rop_inc1<=35&&rop_inc1>=16)
    {
        rop_inc1-=.1;

    }
    else if(rop_inc1<34)
    {
        rop_inc_bool1=0;
        rop_inc1+=.1;

    }
    else
        rop_inc_bool1=1;

//cout<<rop_inc+14<<" "<<7-43<<endl;
    glEnd();

//cout<<add_lef<<endl;
    if(c>=-123 && c<=-120)
    {
        if(add_lef<1)
        {
            game_over();
        }
    }
    glPopMatrix();
//   cout<<add_lef<<endl;
    // cout<<c<<endl;
    // cout<<l_height<<" "<<spt_cutoff<<endl;
    //  glDisable(GL_TEXTURE_2D);
}

void bridge()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[2]);
    glPushMatrix();
    glTranslatef(-32+20,3,-155+45+5+6);
    glScalef(20,2,45);
    cube(1,1,1,0,3);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,v[6]);
    glPushMatrix();
    glTranslatef(-32+-1,-1.5,-155+45+16);
    glScalef(80,2,45);
    cube(1,1,1,0,3);
    glPopMatrix();
    if(c>=-99 &&c<=-50)
    {
        if(mark11||bridge_j)
        {
            b=5.5;
            eyeY = 8;
            bridge_j=1;
            mark11=0;
        }
        else
        {
            game_over();
        }
        bridge_val=3;

        //cout<<"bridge"<<endl;
    }
    else if(c>-50)
    {
        bridge_j=0;
        eyeY = 5;
        bridge_val=0;
    }
    //  cout<<l_height<<" "<<spt_cutoff<<endl;
    glDisable(GL_TEXTURE_2D);
}
void spot_light1(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT1);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1+al3, 1+al3, 1+al3, 1.0};
    GLfloat l_dif[] = {1+dl3,1+dl3,1+dl3,1};
    GLfloat l_spec[] = {1+sl3,1+sl3,1+sl3,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on2)
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT1, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {30};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);

}
void spot_light2(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT2);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1+al3, 1+al3, 1+al3, 1.0};
    GLfloat l_dif[] = {dl3,dl3,dl3,1};
    GLfloat l_spec[] = {sl3,sl3,sl3,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on3)
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT2, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {30};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);

}
void moshal()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,v[15]);
    for(int i=0; i<=95; i+=15)
    {
        glPushMatrix();
        glTranslatef(28.9,5,-155+30+i+5);
        //glRotatef(-25,0,1,0);
        glScalef(1,6,2);
        cube(1,1,1);
        glPopMatrix();
    }

    for(int i=0; i<=115; i+=25)
    {
        glPushMatrix();
        glTranslatef(-29.9,5,-155+30+i+5);
        //glRotatef(-25,0,1,0);
        glScalef(1,6,2);
        cube(1,1,1);
        glPopMatrix();
    }


    glBindTexture(GL_TEXTURE_2D,v[16]);
//rocks
    for(int i=-20; i<=100; i+=15)
    {
        glPushMatrix();
        glTranslatef(15.9,-1,-155+30+i+6+6);
        //glRotatef(-45,0,1,0);
        glScalef(15,3,3);
        cube(1,1,1);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);


}
int control;
void drawStrokeText1(string str,int x,int y,int z,float val=1,int col=0)
{
    //char *c;
    glPushMatrix();
    glLineWidth(1);
    glTranslatef(x, y,z);

  //  glRotatef(184,0,1,0);
    cube(1,col,0,0,1,1);
    glScalef(.004f*val,.004f*val,10);

    for (int c=0; c != str.size(); c++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[c]);
    }
    glPopMatrix();
    //cout<<spt_cutoff<<" "<<l_height<<endl;
}
void light()
{

//light 1
//fire1
//
    if(over)
        is_start=1;

    // l_on1=1-l_on1;
    //  l_on2=1-l_on2;
    //   l_on1=1-l_on1;
    if(!over)
    {
        if(!is_start)
        {

            if(mark11)
                cnt_dwn++;
            if(cnt_dwn>=95||!mark11)
            {
                mark11=0;
                b=1;
                cnt_dwn=0;
            }
            if(left_turn)
            {
                fire();
                point();
                design();
                moshal();
            }
            else
            {
                rope();
                bridge();
                point1();
            }
        }
    }
    glPushMatrix();


    glTranslatef(a+add_lef,b,c);
    glPushMatrix();
    glRotatef(ok,0,1,0);
    if(ok>=360)
        ok=0;
    ok++;
     drawStrokeText1("Sourav",l_height-1.9-.19+.2,3,spt_cutoff+.9);
    player();
 //   cout<<spt_cutoff<<" "<<l_height<<" "<<stop<<" "<<flw<<endl;

    glPopMatrix();

    glPopMatrix();

    //spot light

    glPushMatrix();
    glTranslatef(a+add_lef,18,c+39+13);
    int a1=15,b1=30,c1=-15;
    glRotatef(spt_cutoff-39,0,1,0);
    spot_light1(a1+l_height-157+31,b+1+stop+263,c1+flw-131);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a+add_lef,18,c+39+13);
    a1=15,b1=30,c1=-15;
    glRotatef(spt_cutoff-39+37,0,1,0);
    //spot_light2(a1+l_height-165-157+31,b+1+stop+263+1,c1+flw-131);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a+add_lef,18,c+39+13);
    a1=15,b1=30,c1=-15;
    glRotatef(spt_cutoff+2-39,0,1,0);
    spot_light3(a1+l_height-157+31-40,5+b+1+stop+263,c1+flw-131);
    //   spot_light4(a1+l_height-157+31-40,5+b+1+stop+263,c1+flw-131);
    glPopMatrix();
//cout<<spt_cutoff<<" "<<l_height<<" "<<stop<<" "<<flw<<endl;

    glPushMatrix();
    glPushMatrix();

    glRotatef(200, 0,1,0);
//cout<<add_lef<<" "<<c<<" ->"<<endl;
    if(!is_start)
        a+=lef,c+=fowd;
    light1(a1,b1,c1);
    glPopMatrix();
    glTranslatef(a,b+1,c);

    glScalef(2,2,2);
    glTranslatef(-0.5,-0.5,-0.5);
    //glRotatef(270,0,1,0);
    //cube(1,1,1,1);

    glPopMatrix();
    // cout<<l_height<<" "<<spt_cutoff<<endl;

//light2
    /*
        glPushMatrix();
        glPushMatrix();

        glRotatef(200, 0,1,0);
        float a1=15,b1=17,c1=-15;
        light2(a1,b1,c1);
        glPopMatrix();
        glTranslatef(a1,b1+1,c1);
        glScalef(15,1,1);
        glTranslatef(-0.5,-0.5,-0.5);
        cube(1,1,1,2);
        glPopMatrix();


        //spot light
        glPushMatrix();
        glPushMatrix();
        glRotatef(-95, 0,1,0);
        a1=15,b1=30,c1=-15;
        spot_light(a1,b1,c1);

        glPopMatrix();
        glTranslatef(a1,b1+1,c1);
        glScalef(15,1,1);
        glTranslatef(-0.5,-0.5,-0.5);
        //cube(1,0,0,true);
        glPopMatrix();
        */

    fowd=.08;
    lef=.015;
//cout<<a<<" "<<c<<endl;
    // cout<<sl2<<endl;
    //  cout<<window_val<<endl;
    // cout<<l_height<<" "<<spt_cutoff<<endl;
}
void drawStrokeText(string str,int x,int y,int z,float val=1.15,int col=0)
{
    //char *c;
    glPushMatrix();
    glLineWidth(2);

    glTranslatef(-300+4,0,-300);
    glTranslatef(-15+4-2-4+y, 2+13+bridge_val+z,-155);
    glRotatef(184,0,1,0);
    cube(1,col,0,0,1,1);
    glScalef(.004f*val,.004f*val,10);

    for (int c=0; c != str.size(); c++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[c]);
    }
    glPopMatrix();
    //cout<<spt_cutoff<<" "<<l_height<<endl;
}
char arr11[100];
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);
    gluPerspective(0,0,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, centerX,centerY,centerZ, 0,1,0);

    glRotatef(rot, 0,1,0);

    glPushMatrix();
    glTranslatef(check2,0,check1);
    wall();
    glPushMatrix();
    if(!is_start)
        check1-=.08,check2-=.015;

    glPopMatrix();
    light();

    glPopMatrix();
    glPopMatrix();
    glLineWidth(1);
    stringstream okk;
    okk<<score;
    string str,str1;
    okk>>str;
    okk.clear();
    string str3="";
    for(int i=0; i<life; i++)
    {
        str3+='@';
    }
    glEnable(GL_LINE_SMOOTH);
    str1="       Score:["+str+"]";
    string str2="Life:["+str3+"]";
    //  cout<<arr11<<endl;
    str1=str2+str1;

//over=1;
    //drawStrokeText("Score ",0,0,0);
    // drawStrokeText(arr12,0,0,4);
    if(!over)
    {
        if(!is_start)
            drawStrokeText(str1,0,0,0);
        if(is_start)
            drawStrokeText("Press v for strat the game",0,6,-6);
        if(is_start)
            drawStrokeText("Press 0 for change character name",0,6,-7);
        if(is_start)
            drawStrokeText("Press q for quiet game",0,6,-8);
        if(is_start)
            drawStrokeText("Maze Runner 3D",0,6,-2,3.0,1);
    }
    else
    {
        str="Score:"+str;
        drawStrokeText("Maze Runner 3D",0,6,-2,3.0,1);
        drawStrokeText("Game Over",0,-1,-5,2.0);
        drawStrokeText(str,0,-1,-7,2.0);
    }
    // if(check3<=50)check3=50,check4-=.015;

    //cout<<check3<<endl;
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y);


static void light14(unsigned char light1, int x, int y)
{

    switch (light1)
    {

    case 27:
        glutKeyboardFunc(key);
        break;
    case '1':
        al1+=l_val;
        break;
    case '2':
        al1-=l_val;
        break;
    case '3':
        dl1+=l_val;
        break;
    case '4':
        dl1-=l_val;
        break;
    case '5':
        sl1+=l_val;
        break;
    case '6':
        sl1-=l_val;
        break;
    }
read:
    return;
}

static void light24(unsigned char light2, int x, int y)
{
    switch (light2)
    {

    case 27:
        glutKeyboardFunc(key);

        break;
    case '1':
        al2+=l_val;
        break;
    case '2':
        al2-=l_val;
        break;
    case '3':
        dl2+=l_val;
        break;
    case '4':
        dl2-=l_val;
        break;
    case '5':
        sl2+=l_val;
        break;
    case '6':
        sl2-=l_val;
        break;
    }
}

static void spot_light14(unsigned char spot_light, int x, int y)
{
    switch (spot_light)
    {

    case 27:

        glutKeyboardFunc(key);
        break;
    case '1':
        al3+=l_val;
        break;
    case '2':
        al3-=l_val;
        break;
    case '3':
        dl3+=l_val;
        break;
    case '4':
        dl3-=l_val;
        break;
    case '5':
        sl3+=l_val;
        break;
    case '6':
        sl3-=l_val;
        break;
    }
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 27:
        exit(0);
        break;
    case '+':
        eyeZ++;
        //eyeY++;
        break;
    case '-':
        eyeZ--;
        // eyeY--;
        break;

    case 'a':
        eyeX++;

        //eyeY++;
        break;
    case 's':
        eyeX--;
        // eyeY--;
        break;

    case 'g':
        eyeY++;
    case 'v':
        is_start=0;
        //eyeY++;
        break;
    case 'h':
        eyeY--;
        // eyeY--;
        break;

    case 'w':
        //centerX++;
        centerY++;
        //  centerZ++;
        break;
    case 'e':
        //  centerX--;
        centerY--;
        //  centerZ--;
        break;

    case 'o':
        centerX+=2;

        //centerY++;
        //  centerZ++;
        break;
    case 'p':
        centerX-=2;
        //centerY--;
        //  centerZ--;
        break;

    case 'k':
        centerZ++;
        //centerY++;
        //  centerZ++;
        break;
    case 'l':
        centerZ--;
        //centerY--;
        //  centerZ--;
        break;


    case ',':
        rot++;
        break;
    case '.':
        rot--;
        break;

    case '*':
        stop=0;
        break;



    case '1':
        l_height+=.1;
        break;
    case '2':
        l_height-=.1;
        break;

    case '3':
        spt_cutoff+=.1;
        break;
    case '4':
        spt_cutoff-=.1;
        break;
    case '5':
        flw+=.1;
        break;
    case '6':
        flw-=.1;
        break;
    case '7':
        stop+=.1;
        break;
    case '8':
        stop-=.1;
        break;

    case 'u':
        if(cnt_dwn==0)
        {
            b=6;
            mark11=1;
        }
        break;
    case 't':
        add_lef+=.2;

        if(add_lef>2)
            add_lef=2;
        break;



    case 'y':
        add_lef-=.2;
        if(add_lef<-3)
            add_lef=-3;
        break;

    case 'b':
        reset();
        left_turn=1-left_turn;
        break;
    case 'm':
        glutKeyboardFunc(spot_light14);
        break;

    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
 spin();
}

/* Program entry point */
void texture_image()
{
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\brick road1.bmp");//0
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\head.bmp");//1
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\top.bmp");//2
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\brick road.bmp");//3
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\door1.bmp");//4
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\spike.bmp");//5
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\fire.bmp");//6
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\gold.bmp");//7
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\momy.bmp");//8
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\mask.bmp");//9
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\grash.bmp");//10
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\wall2.bmp");//11
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\top2.bmp");//12
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\backwall.bmp");//13
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\laser.bmp");//14
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\flame.bmp");//15
    v.push_back(ID);
    LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\rock.bmp");//16
    v.push_back(ID);
     LoadTexture("C:\\Users\\Sourav\\Desktop\\ui\\figures\\face.bmp");//17
    v.push_back(ID);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(550,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Maze Runner 3D");
    glutReshapeFunc(res);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);
    GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    texture_image();
    int t=1;
    printf("Warning!!! please turn off caps lock and use shift key before * key and + key.\n");
    printf("%d. Press 't' for off light1.\n",t++);
    printf("%d. Press 'y' for off light2.\n",t++);
    printf("%d. Press 'u' for off cse light.\n",t++);

    printf("%d. Press '*' for stop fans.\n",t++);
    printf("%d. Press ';' for start fans.\n",t++);
    printf("%d. Press 'd' for window open/close.\n",t++);
    printf("%d. Press 'w' for up.\n%d. press 'e' for down.\n%d. press 's' for right.\n%d. press 'a' for left.\n",t+1,t+2,t+3,t+4);
    t+=4;
    printf("%d. Press 'o' to move camera left.\n%d. Press 'p' to move camera right.\n",t+1,t+2);
    t+=2;
    printf("%d. Press '+' to zoom in.\n%d. Press '-' for zoom out.\n",t+1,t+2);
    t+=2;
    printf("%d. Press b,n,m for operate with light1,light2 and CSE light respectively.\n",t++);
    printf("   1. Press '1' for add ambient.\n");
    printf("   2. Press '2' for reduce ambient.\n");
    printf("   3. Press '3' for add diffuse.\n");
    printf("   4. Press '4' for reduce diffuse.\n");

    printf("   5. Press '5' for add specular light.\n");
    printf("   6. Press '6' for reduce specular light.\n");
    printf("   7. Press ESC key for exit this operation and goto main programme\n");

    printf("%d. Press ESC key for exit the main programme\n",t++);

    glutMainLoop();

    return EXIT_SUCCESS;
}
