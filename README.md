# RenderGPU
Segona pràctica de GiVD 2021-22


## Equip:
**AB01**
* Endimbeer Enrique Nuñez Matos
* Chan YE
* Noel Vázquez Caparrós
* Pau Rodríguez Trens
    
**Abstract**

Aquesta pràctica és una continuació de l'anterior. El que hem fet és agafar algunes de les classes definides prèviament com a base i a partir d'aquí adaptar-les i afegir canvis per poder fer ús de la GPU mitjançant shaders (Phong, Gouraud, Toon Shading...). A més, hem modificat la classe Mesh perquè pugui tenir una textura i els seus vèrtexs de textura associats a cada punt de l'objecte.

**Features**

- Fase 1
    - Adaptació a la lectura de fitxers de dades
        - [x] Objectes
          - Endimbeer Enrique Nuñez Matos
          - Chang Ye
        - [x] Escenes virtuals
          - Noel Vázquez Caparrós
          - Chang Ye
        - [ ] Escenes de dades Reals 
    - Material
        - [x] Classe material
           - Endimbeer Enrique Nuñez Matos
    - Light
        - [x] Puntual
          - Pau Rodríguez Trens
        - [x] Direccional
          - Pau Rodríguez Trens
        - [ ] Spotlight
        - [x] Ambient Global
          - Pau Rodríguez Trens
    - Shading
        - [x] Depth
          - Endimbeer Enrique Nuñez Matos
          - Chang Ye
        - [x] Phong
          - Pau Rodríguez Trens
        - [x] Gouraud
          - Pau Rodríguez Trens
        - [x] Toon-shading
          - Endimbeer Enrique Nuñez Matos
          - Chang Ye
    - Textures
        - [x] Textura com material en un objecte
          - Endimbeer Enrique Nuñez Matos
        - [ ] Textura al pla base
          

- Fase 2 
    - [ ] Èmfasi de siluetes
    - [ ] Mapping indirecte de textures
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping
    - [x] Entorn amb textures
    - Chang Ye
    - [ ] Reflexions
    - [ ] Transparències via objectes.
    - [ ] Transparències via environmental mapping.


**Extensions**

*(NOTA: Les extensions de la pràctica que heu fet i que no surten a la llista anterior)*

**Memòria**

  * **Organització de la pràctica**
        * Hem dividit els diferents apartats de la pràctica en parelles amb l'objectiu de poder ajudar-nos amb els dubtes. També hem realitzat sessions de pair programming per poder afrontar alguns apartats. 
  ### 1) Construcció de l’escena virtual a partir de fitxers .obj, dades virtuals o dades geolocalitzades (adaptació del codi de la pràctica 1)
El primer que hem fet és afegir el codi necessari a la classe Builder per poder llegir un `.json` que contingui la informació necessària per crear una escena virtual. 

Per a aconseguir això comprovem al mètode newVirtualScene que ens passin el nom d'un fitxer i que existeixi. A continuació llegim el seu contingut i el guardem en un `QJsonObject`. Finalment, per a cada objecte de l'escena cridem al constructor i en cas que tingui un material el llegim, li assignem i afegim l'objecte a la llista `vector<shared_ptr> objects` de l'escena.

  ### 2) Modificació de la classe Material i pas a la GPU dels valors de materials
En aquest pas se'ns demana basar-nos en la classe `Material` de la pràctica de `Raytracing` i afegir el codi necessari per poder passar les seves dades (Components especular, ambiental i difusa, shininess i opacitat) als shaders de la GPU. 

Simplement, hem afegit els mètodes constructors (amb paràmetres i amb valors 'hardcodejats'), `read (const QJsonObject &json)`, `write(QJsonObject &json) const`, `print(int indentation) const` i `toGPU(shared_ptr program)`.

El mètode `toGPU` és el més interessant de tots, ja que és el que ens permet passar els valors del material als shaders, cosa que necessitarem per implementar models com el de `Blinn Phong`. Aquest mètode el cridarem des del draw de Mesh.cpp `this->material->toGPU(program)`. El que fem és definir structs tant a la CPU com a la GPU per organitzar la informació del nostre material.

<pre>
//Struct material a CPU <br />
struct {<br />
    GLuint kd; <br />
    GLuint ks; <br />
    GLuint ka; <br />
    GLuint shine; <br />
    GLuint opac; <br />
}gl_material; <br />

//Struct material a GPU <br />
struct mtr{ <br />
    vec3 Kd; <br />
    vec3 Ka; <br />
    vec3 Ks ;<br />
    float shininess; <br />
    float opacity; <br />
};<br />
uniform mtr material;<br />
</pre>

Llavors des del codi C++ el que fem és aconseguir els identificadors de la GPU per a cada dada de l'struct, com per exemple a `gl_material.kd = program->uniformLocation("material.Kd")`.

A continuació, també desde la classe `Material.cpp` fem el bind de les zones de memòria que corresponen a la GPU a valors de les variables de l'struct de la CPU, com per exemple a `glUniform3fv(gl_material.kd, 1, Kd)`.

  ### 3) Modificació de la classe llum i pas a la GPU
De forma molt similar al material del pas anterior, en aquest se'ns demana basar-nos en la classe `Light` de la pràctica de 'Raytracing' i afegir el codi necessari per poder passar les seves dades (Components especular, ambiental i difusa...) als shaders de la GPU. 

A més, tindrem dos tipus de llums, `Puntuals` i `Direccionals`. Les llums puntuals no tenen dimensió, ni direcció (emeten en forma radial). Es caracteritzen per la posició i la seva emissió (o intensitat). Per altra banda les llums direccionals tenen un focus a l'infinit i es caracteritzen per la seva direcció i intensitat.

Aquests dos tipus de llum (també hi ha un tercer tipus 'Spot' opcional que NO hem implementat) no s'implementen mitjançant una jerarquia de classes que hereti de `Lihgt.h` com a la pràctica anterior, sino que dintre de Light tenim definit un LightType de tipus enum que ens permet saber si la llum es Puntual o Direccional. Per tant tindrem un constructor comú als diferents tipus de llum i una llista de llums a l'escena, que s'afegeixen desde el métode `initializeGL` a `GLWidget`.

Finalment, per enviar les dades a la GPU el procés és exactament el mateix que amb el material en quant a la definició dels structs:


<pre>
//Struct llums a CPU <br />
struct lightsid
{
    GLuint type; <br />
    GLuint lightIS; <br />
    GLuint lightID; <br />
    GLuint lightIA; <br />
    GLuint coeficients; <br />
    GLuint lightPosition; <br />
    GLuint lightDirection; <br />
};
lightsid gl_IdLightsVec[MAX];

//Struct llums a GPU
struct lightsGpu
{
    int lightType_gpu; <br />
    vec3 lightIS_gpu; <br />
    vec3 lightID_gpu; <br />
    vec3 lightIA_gpu; <br />
    vec3 coeficients_gpu; <br />
    vec4 lightPosition_gpu; <br />
    vec4 lightDirection_gpu; <br />
};
uniform lightsGpu lights[1];
</pre>

Llavors des del codi C++ el que fem és aconseguir els identificadors de la GPU per a cada dada de l'struct, com per exemple a `    gl_IdLightsVec[i].type = program->uniformLocation(QString("lights[%1].lightType_gpu").arg(i))`.

A continuació, també desde la classe `Light.cpp` fem el bind de les zones de memòria que corresponen a la GPU a valors de les variables de l'struct de la CPU, com per exemple a `glUniform1i(gl_IdLightsVec[i].type, this->typeLight)`.

Per altra banda, és important tenir en compte que el mètode `Light::LightsToGPU` es crida a `Scene::lightsToGPU`. El que fem és un bucle a `Scene.cpp` que passa per totes les llums de la seva llista i per cada una d'elles crida al seu mètode LightsToGPU. I el mètode `Scene::lightsToGPU` es crida des de `GLWidget::initializeGL()` i també al mètode general `toGpu` de `Scene.cpp` (on a part de les llums també s'envia la informació dels objectes de la llista). 

Finalment, la llum d'ambient global s'envia des de l'escena `setAmbientGlobalToGPU(shared_ptr program)` a `GLWidget::initializeGL()` i el toGpu de l'escena es crida també a `GLWidget` des de `updateObject` (cada vegada que carreguem un objecte), `updateScene` i `activaShader` (cada vegada que canviem de shader).

  ### 4) Implementació dels diferents tipus de shading (depth, Gouraud, Phong i toon-shading)
En aquest apartat se'ns demana implementar 4 tipus de shading: Depth Shading, Gouraud, Phong i Toon Shading. Per a aconseguir això el que haurem de fer és crear diferents parelles de shader de tipus Vèrtex i Fragment '.glsl' a '/resources'. En general, aquests shaders necessitaran la posició del punt, normals als vèrtex, les llums, els materials i la llum ambiental global.

Tal com hem explicat anteriorment, les llums, els materials i la llum ambiental global ja s'estan enviant des dels seus respectius mètodes toGpu. Per tant, el que falta és enviar les normals. Això ho haurem de fer des de 'Mesh.cpp'. Desde la Mesh calculem la normal a cada vèrtex a la CPU mitjançant un doble bucle for que passa per tots els vèrtex de totes les cares.

<pre>
    points[Index] = vertexs[cares[i].idxVertices[j]];
    normals[Index] = normalsVertexs[cares[i].idxNormals[j]];
</pre>

Per altra banda, un cop calculades enviem les normals a la GPU amb el mètode 'Mesh::toGPU(shared_ptr pr)' a 'glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, normals)'.

Finalment, un cop ja tenim totes les dades només queda implementar les fórmules de Phong, Gouraud, Depth i Toon als seus respectius shaders.

* **Blinn Phong**
<br />Implementació de la fórmula de Blinn Phong al fhsader:
![image](https://user-images.githubusercontent.com/72156170/169694406-8484427b-c2fb-4c27-bfca-18545d3b8681.png)

* Gouraud
<br />En el cas de Gouraud, la diferència amb Phong és que en comptes de fer el càlcul de la Itotal al fshader, ho fem al vshader. D'aquesta manera aconseguim tenir el promig de les normals a cada vèrtex, aplicar el model de `Blinn-Phong` a cadascun dels vèrtexs i interpolar les intensitats de cada vèrtex a cada polígon.

* Toon shading
<br />A Toon shading el que busquem és que els objectes tinguin una il·luminació similar a l'estil cartoon. Per aconseguir això calculem el producte entre el vector L (vector normalitzat entre la llum i el punt) i la normal i limitem el color resultant en quatre nivells amb una variable factorToon al fshader.
<pre>
toon = dot(L,N);

if(toon>=0.25 && toon<=0.5)
    factorToon = 0.25;
else if(toon<0.75)
    factorToon = 0.50;
else if(toon >= 0.75)
    factorToon = 0.75;
</pre>
* Depth shading
<br />Finalment, amb el Depth shading volem pintar en grisos la profunditat del triangle que s'ha rasteritzat en el píxel. Això ho aconseguim des de el fragment shader 'depth_fshader.glslde' la següent forma:

<pre>

    float factorDepth = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far)
            / (gl_DepthRange.far - gl_DepthRange.near);

    float clipDepth = factorDepth / gl_FragCoord.w;
    colorOut = vec4((clipDepth * 0.5) + 0.5);
</pre>

És important remarcar també que en carregar per primera vegada una escena, carreguem per defecte un dels shaders de la nostra llista a `GLWidget` després de compilar-los des de `initShadersGPU`, tot i que es poden canviar en qualsevol moment gràcies als diferents mètodes `activaPhongShader`, `activaDepthShader`...

<pre>
    initShadersGPU();
    program = shader_list[2];
    shader_list[2]->link();
    shader_list[2]->bind();
</pre>

  ### 5) Inclusió de les textures en les nostres visualitzacions
En aquest apartat se'ns demana incloure textures en la visualització dels objectes que es carreguin. En els '.obj' tenim les coordenades de textura de les malles poligonals, i amb aquestes coordenades passades al fragment shader podem obtenir els píxels associats a cada píxel on es rasteritza l'objecte.

Per a aconseguir això un dels mètodes més importants és el 'initTexture' de 'Mesh.cpp', que ens permet inicialitzar la textura de l'objecte i fer el bind.
<pre>
void Mesh::initTexture()
{
    qDebug() << "Initializing textures...";
    glActiveTexture(GL_TEXTURE0);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->bind(0);
}
</pre>

Igual que els materials, les llums i les normals, també hem d'enviar les coordenades de textures a la GPU amb el mètode:
<pre>
void Mesh::toGPUTexture(shared_ptr<QGLShaderProgram> pr){
    texture->bind(0);
    pr->setUniformValue("texMap", 0);
}
</pre>

Des de 'text_phong_vshader.glsl' rebem les coordenades i les passem al fragment shader 'text_phong_fshader.glsl':

<pre>
layout (location = 2) 
in vec2 vCoordTexture;
out vec2 v_texcoord;
...
v_texcoord = vCoordTexture;
</pre>

Finalment, des de 'text_phong_fshader.glsl' simplement rebem les coordenades de textura i la textura 'texMap' que ens ha passat el vèrtex shader i ho afegim a la component difusa de Blinn Phong de la següent manera:

<pre>
out vec4 colorOut;
uniform sampler2D texMap;
...

idkd = lights[i].lightID_gpu * (texture(texMap, v_texcoord).rgb)  * max(dot(N,L), 0.0);
isks = lights[i].lightIS_gpu * material.Ks * pow(max(dot(N,H), 0.0), material.shininess);
iaka = lights[i].lightIA_gpu * material.Ka;
//Para hacer pruebas con los ejemplos del campus hemos quitado la atenuación de la fórmula de phong
//Itotal += ((idkd + isks)/attenuation) + iaka;
Itotal += ((idkd + isks)/attenuation) + iaka;
</pre>


**Screenshots**

*(NOTA: Captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

- Fase 1
    - Adaptació a la lectura de fitxers de dades
      Escenas virtuales y lectura de objetos desde un fichero JSON.
      Escena compuesta por las figuras de armadillo y el avión F16. 
    ![image](https://user-images.githubusercontent.com/72166134/169703340-2453b547-7d0f-44f9-ba39-      84e489ffec86.png)

    - Material y Light
    
    Pruebas del paso de las diferentes componentes a la GPU tanto para la luz como para el meterial: 
    
    Componente difusa:
    ![image](https://user-images.githubusercontent.com/72166134/169706326-74ad48cd-c8ce-4365-91f7-8aa089ef6544.png)

    Componente ambiental:
    ![image](https://user-images.githubusercontent.com/72166134/169706490-d44411c2-2457-4c47-ae74-5a8a37631755.png)

    
    Componente Especular:
    ![image](https://user-images.githubusercontent.com/72166134/169706639-0635dd63-04c7-4932-8ef0-b4ebf1dcd909.png)

    - Shading
        -Depth 
        Imagen generada mediante el fichero f16.obj
        
![image](https://user-images.githubusercontent.com/72166134/169707708-9097871c-9041-436f-9626-5bcdbba1fae8.png)

         Imagen generada mediante el fichero sphere0.obj:
         Kd =(0.8,0.5,0.5)
         Ka = (0.2,0.2,0.2)
         Ks =(1.,1.,1.)
         shineness 20;
         Luz Puntual a (10, 10, 20)
         Id= (0.8,0.8,0.8)
         Is = (1,1,1)
         Ia = (0.2,0.2,0.2)
         Luz Ambiente gloabl (0.3, 0.3, 0.3)

         **Phong**

         ![image](https://user-images.githubusercontent.com/72166134/169707850-7fcaedff-5cbc-479e-b2b6-022b58f384e9.png)

        ![image](https://user-images.githubusercontent.com/72166134/169708007-b0638070-2e2a-4a20-9651-bb2511faf0eb.png)

        
        **Gouraud**
        ![image](https://user-images.githubusercontent.com/72166134/169707856-0e3b1d89-72d4-44ea-9911-af8317a8aac2.png)

        
        -Toon-shading
        ![image](https://user-images.githubusercontent.com/72166134/169707927-dea0e5ba-44ec-47fb-ae56-da53b164767b.png)
    
        ![image](https://user-images.githubusercontent.com/72166134/169708108-8150c990-9efc-4006-9c90-40ae865ad1d7.png)

    - Texturas
      Textura con material en un objeto

![Captura de pantalla 2022-05-22 201019](https://user-images.githubusercontent.com/72166134/169709729-9d162c10-6704-44e8-8ffd-d279a2082bb1.png)


**Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*

**Endimbeer Enrique Nuñez Matos
He empleado unas 4 horas a la semana, salvo en los últimos días en los cuales he dedicado prácticamente 2 o 3 días solo a la práctica. Mi principal problema han sido los errores con el orden en el cuál importaba las librerías que provocaban que el programa fallara. 

También me costó la parte de texturas debido a que no controlaba si el fichero se había cargado o no. 


