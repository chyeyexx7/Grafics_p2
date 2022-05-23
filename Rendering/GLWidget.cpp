#include "Rendering/GLWidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    scene = make_shared<Scene>();
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
}

GLWidget::~GLWidget() {
}


void GLWidget::setScene(shared_ptr<Scene> sc) {
    scene = sc;
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

/* Interacció amb GL i inicialització de shaders */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    //Inicializamos la lista de shaders
    initShadersGPU();
    //Indicamos que shader de la lista queremos utilizar
    useShader(ShaderType::PHONG);

    // Creacio d'una Light per a poder modificar el seus valors amb la interficie
    auto l  = make_shared<Light>(Puntual);
    scene->addLight(l);
    scene->setAmbientGlobalToGPU(program);

    scene->camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
    scene->lightsToGPU(program);
    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    if (scene->CUBEMAP) {
        useShader(ShaderType::CUBEMAP);
        if (cubeTexture) {
            // Seteamos textura de cub una única vez
            scene->cub->initTextura();
            cubeTexture = false;
        }
        scene->camera->toGPU(program);
        scene->cub->toGPU(program);
        scene->cub->draw();
        useShader(currentShader);
    }
    scene->toGPU(program);
    scene->camera->toGPU(program);
    scene->draw();
    qDebug() << "paint";
}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    scene->camera->vp.a = width;
    scene->camera->vp.h = height;

    scene->camera->CalculaWindow(scene->capsaMinima);

    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    initShader(0, "://resources/depth_vshader.glsl", "://resources/depth_fshader.glsl");
    initShader(1, "://resources/phong_vshader.glsl", "://resources/phong_fshader.glsl");
    initShader(2, "://resources/gouraud_vshader.glsl", "://resources/gouraud_fshader.glsl");
    initShader(3, "://resources/toon_vshader.glsl", "://resources/toon_fshader.glsl");
    initShader(4, "://resources/text_phong_vshader.glsl", "://resources/text_phong_fshader.glsl");
    initShader(5, "://resources/cube_vshader.glsl", "://resources/cube_fshader.glsl");
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

/**
 * @brief GLWidget::initShader()
 * Compila i linka el vertex i el fragment shader
 */
void GLWidget::initShader(int shader, const char* vShaderFile, const char* fShaderFile){
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    //program = make_shared<QGLShaderProgram>(this);
    //program->addShader(vshader);
    //program->addShader(fshader);
    //program->link();
    //program->bind();

    shader_list[shader] = make_shared<QGLShaderProgram>(this);
    shader_list[shader]->addShader(vshader);
    shader_list[shader]->addShader(fshader);
}

/** Gestio de les animacions i la gravació d'imatges ***/

void GLWidget::setCurrentFrame(){

    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){

    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */
void GLWidget::updateObject(shared_ptr<Mesh> obj) {
    initShadersGPU();
    obj->toGPU(program);
    //scene->toGPU(program);
    updateGL();
}

void GLWidget::updateScene(shared_ptr<Scene> sc) {
    // Control de la nova escena a la GPU
    scene = sc;
    scene->toGPU(program);

    // Podeu utilitzar l'altre constructor de Camera per inicialitzar els parametres de la camera.
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();

}

/** Metodes que es criden des dels menús */

void GLWidget::saveAnimation() {
    // Comença el timer de l'animació
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaDepthShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Depth";
    currentShader = ShaderType::DEPTH;
    useShader(currentShader);
    updateShader();
}

void GLWidget::activaGouraudShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Gouraud";
    currentShader = ShaderType::GOURAUD;
    useShader(currentShader);
    updateShader();

}
void GLWidget::activaPhongShader() {
    //Opcional: A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong";
    currentShader = ShaderType::PHONG;
    useShader(currentShader);
    updateShader();
}
void GLWidget::activaToonShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Toon";
    currentShader = ShaderType::TOON;
    useShader(currentShader);
    updateShader();

}

void GLWidget::activaPhongTex() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong Tex";
    currentShader = ShaderType::TEXT_PHONG;
    useShader(currentShader);
    updateShader();

}

void GLWidget::activaBackground() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Background";

}
void GLWidget::activaBumpMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
     qDebug()<<"Estic a Bump Mapping";
}

void GLWidget::activaEnvMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Environmental Mapping";
    if (scene->CUBEMAP == false) {
        scene->cub = make_shared<Cub>();
        scene->CUBEMAP = true;
    }
    useShader(ShaderType::CUBEMAP);
    updateShader();
}

void GLWidget::activaTransparency() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Transparencia";
}

//Metode  per canviar de shaders.
void GLWidget::updateShader(){
    scene->toGPU(program);
    updateGL();
}

//Metode per canviar de shaders de textures
void GLWidget::updateShaderTexture(){
    //A implementar a la fase 1 de la practica 2

}

/** Mètodes que es criden des de les finestres de dialeg */

void GLWidget::setRotation(float angle, float x, float y, float z)
{
    // Rotació en coordenades de mon que es farà sobre l'escena carregada

}
void GLWidget::setTranslation(float x, float y, float z)
{
    // Translació en coordenades de mon que es farà sobre l'escena carregada

}

void GLWidget::setScale(float s)
{
    // Escala en coordenades de mon que es  farà sobre l'escena carregada
}


void GLWidget::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    scene->camera->setFrustum(verticalAngle, nearPlane, farPlane);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);
    scene->camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec4 lightPosition(lightPos[0],lightPos[1], lightPos[2], 1.0) ;
    vec3 intensityA( Ia[0], Ia[1], Ia[2]);
    vec3 intensityD( Id[0], Id[1], Id[2]);
    vec3 intensityS( Is[0], Is[1], Is[2]);

    scene->lights[0]->setIa(intensityA);
    scene->lights[0]->setId(intensityD);
    scene->lights[0]->setIs(intensityS);
    scene->lights[0]->setLightPosition(lightPosition);
    scene->lightsToGPU(program);
    updateGL();
}

void GLWidget::setTextureFile(const QString &file)
{
    shared_ptr<QOpenGLTexture> texture;

    texture = make_shared<QOpenGLTexture>(QImage(file).mirrored());

    // TO DO: A modificar en la fase 1 de la practica 2
    // Per ara es posa la textura al primer objecte de l'escena
    scene->objects[0]->setTexture(texture);

}

/**  Mètodes d'interacció amb el ratolí */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    if (angle >0) {
        scene->camera->angX += 5;
    } else if (angle<0)
        scene->camera->angX -= 5;
    qNormalizeAngle(scene->camera->angX);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    if (angle >0) {
        scene->camera->angY += 5;
    } else if (angle<0)
        scene->camera->angY-= 5;
    qNormalizeAngle(scene->camera->angY);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {
    scene->camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::useShader(ShaderType s) {
    switch (s) {
        case DEPTH:
            program = shader_list[0];
            break;
        case PHONG:
            program = shader_list[1];
            break;
        case GOURAUD:
            program = shader_list[2];
            break;
        case TOON:
            program = shader_list[3];
            break;
        case TEXT_PHONG:
            program = shader_list[4];
            break;
        case CUBEMAP:
            program = shader_list[5];
            break;
        default:
            program = shader_list[1];
    }
    program->link();
    program->bind();
}

