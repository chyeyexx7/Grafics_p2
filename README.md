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
En aquest pas se'ns demana basar-nos en la classe 'Material' de la pràctica de 'Raytracing' i afegir el codi necessari per poder passar les seves dades (Components especular, ambiental i difusa, shininess i opacitat) als shaders de la GPU. 

Simplement, hem afegit els mètodes constructors (amb paràmetres i amb valors 'hardcodejats'), 'read (const QJsonObject &json)', 'write(QJsonObject &json) const', 'print(int indentation) const' i 'toGPU(shared_ptr program)'.

El mètode 'toGPU' és el més interessant de tots, ja que és el que ens permet passar els valors del material als shaders, cosa que necessitarem per implementar models com el de Blinn Phong. Aquest mètode el cridarem des del draw de Mesh.cpp 'this->material->toGPU(program)'. El que fem és definir structs tant a la CPU com a la GPU per organitzar la informació del nostre material.

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

A continuació, també desde la classe `Material.cpp` fem el bind de les zones de memòria que corresponen a la GPU a valors les variables de l'struct de la CPU, com per exemple a `glUniform3fv(gl_material.kd, 1, Kd)`.

  ### 3) Modificació de la classe llum i pas a la GPU
De forma molt similar al material del pas anterior, en aquest se'ns demana basar-nos en la classe 'Light' de la pràctica de 'Raytracing' i afegir el codi necessari per poder passar les seves dades (Components especular, ambiental i difusa...) als shaders de la GPU. 

A més, tindrem dos tipus de llums, `Puntuals` i `Direccionals`. Les llums puntuals no tenen dimensió, ni direcció (emeten en forma radial). Es caracteritzen per la posició i la seva emissió (o intensitat). Per altra banda les llums direccionals tenen un focus a l'infinit i es caracteritzen per la seva direcció i intensitat.

Aquests dos tipus de llum (també hi ha un tercer tipus `Spot` opcional que NO hem implementat) no s'implementen mitjançant una jerarquia de classes que heredi de `Lihgt.h` com a la pràctica anterior, sino que dintre de Light tenim definit un LightType de tipus enum que ens permet saber si la llum es Puntual o Direccional. Per tant tindrem un constructor comú als diferents tipus de llum i una llista de llums a l'escena, que s'afegeixen desde el métode `initializeGL` a `GLWidget`.

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

A continuació, també desde la classe `Light.cpp` fem el bind de les zones de memòria que corresponen a la GPU a valors les variables de l'struct de la CPU, com per exemple a `glUniform1i(gl_IdLightsVec[i].type, this->typeLight)`.

Per altra banda, és important tenir en compte que el mètode `Light::LightsToGPU` es crida a `Scene::lightsToGPU`. El que fem és un bucle a `Scene.cpp` que passa per totes les llums de la seva llista i per cada una d'elles crida al seu mètode LightsToGPU. I el mètode `Scene::lightsToGPU` es crida des de `GLWidget::initializeGL()` i també al mètode general `toGpu` de `Scene.cpp` (on a part de les llums també s'envia la informació dels objectes de la llista. 

Finalment, la llum d'ambient global s'envia des de l'escena `setAmbientGlobalToGPU(shared_ptr program)` a `GLWidget::initializeGL()` i el toGpu de l'escena es crida també a `GLWidget` des de `updateObject` (cada vegada que carreguem un objecte), `updateScene` i `activaShader` (cada vegada que canviem de shader).

**Screenshots**

*(NOTA: Captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

**Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*
