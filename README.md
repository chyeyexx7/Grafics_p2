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

//Struct material a CPU <br />
**struct {<br />
    GLuint kd; <br />
    GLuint ks; <br />
    GLuint ka; <br />
    GLuint shine; <br />
    GLuint opac; <br />
}gl_material; <br />

//Struct material a GPU <br />
**struct mtr{ <br />
    vec3 Kd; <br />
    vec3 Ka; <br />
    vec3 Ks ;<br />
    float shininess; <br />
    float opacity; <br />
};<br />
uniform mtr material;<br />
    
Llavors des del codi C++ el que fem és aconseguir els identificadors de la GPU per a cada dada de l'struct, com per exemple a `gl_material.kd = program->uniformLocation("material.Kd")`.

A continuació, també desde la classe `Material.cpp` fem el bind de les zones de memòria que corresponen a la GPU a valors les variables de l'struct de la CPU, com per exemple a `glUniform3fv(gl_material.kd, 1, Kd)`.

**Screenshots**

*(NOTA: Captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

**Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*
