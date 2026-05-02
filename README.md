# neogba

neogba es un software para la emulación de títulos de GBA.

## Motivación

- Este proyecto no busca ser un reemplazo a los emuladores de GBA más establecidos.
- Este proyecto no busca ser un software para el juego y entretenimiento.
- Este proyecto no busca emulación 1:1.
- Este proyecto no implementa el conjunto de instrucciones de GB.
- Este proyecto se enfoca en el estudio de la arquitectura de la GBA y su procesador ARM7TDMI exclusivamente.
- Este proyecto busca implementar un conjunto de características básicas y de mayor interés (gráficos).
- Este proyecto busca conocer más acerca sobre la preservación del software adoptando estrategias de bajo nivel.

## Diario de desarrollo

He empezado recopilando información acerca de esta consola. Artículos, documentación técnica, otros emuladores/simuladores, blogs y vídeos me han sido de ayuda para familiarizarme con la arquitectura hardware de la consola. He aprovechado para preguntar a profesores especializados en materia de retrocomputación y exponer formalmente una presentación sobre la GBA en clase.

Sobre la GBA:

- La GBA es consola que tiene dos procesadores uno heredado para títulos de GBC y otro ARM7TDMI para los títulos de la GBA.
- En la GBA no se utilizan a la vez ambos procesadores.
- ARM7TDMI es una implementación de la arquitectura ARMv4T, implicando la implementación del conjunto de instrucciones Thumb.
- Una instrucción Thumb ocupa 16 bits frente a 32 bits de las ARM normales. 
- ARM7TDMI puede alternar entre modalidades de instrucciones Thumb y ARM durante la ejecución de un programa.
- El procesador ARM7 es bi-endian pero la GBA opera exclusivamente bajo litte-endian.
- ARM7TDMI es ejemplo clásico de la arquitectura ARM que emplea registros bancados, los cuales su accesibilidad es limitada a las diferentes modalidades de operación del procesador mientras que otros son compartidos. 
- La GBA es compatible con una numerosa cantidad de accesorios y funcionalidades tales como multijugador, cámara, comunicación con otras consolas... 
- La GBA proporciona más entradas que su generación anterior.
- La GBA ofrece la opción de vídeo 3D con las restricciones de la época. Además ofrece diferentes modos de render tanto para gráficos 2D como 3D que tiene más o menos restricciones (Ejemplo: transformaciones afines, paletas, capas...).

Tras investigar inicialmente, me he puesto como objetivos (1) Implementar el conjunto de instrucciones de ARM7TDMI, (2) Implementar un función de desensamblado de un programa en ARMv4T y (3) Implementar el dibujado de gráficos. Para este último propósito he barajado en hacer servir una biblioteca de manipulación de gráficos raylib. 

Raylib es una biblioteca popular de código abierto surgida inicialmente como una herramienta para programar gráficos dirigida a alumnos de artes. Es un recurso multiplataforma y con diversas extensiones para expandir sus funcionalidades.

He decido utilizar C++ con gtest (biblioteca de testing y mocking de Google para C++). No obstante, cabe mencionar que he barajado la opción de hacerlo bajo Rust. Pero debido a posibles contratiempos que puedan surgir, he descartado esta opción rápidamente. En su lugar he optado por utilizar una plantilla de C++ con testing y seguir un estilo de código lo más cercano a C++ idiomático y seguir unos principios de código típicos al paradigma de la programación orientada a objetos (POO). Este lenguaje pese a traer sus inconvenientes y desventajas frente a otras alternativas, sigue siendo uno de los más relevancia en la industria para el empleo. 

Inicialmente empecé con la implementación de los registros de la CPU. La implementación optada fue una estructura de una lista de todos los 37 registros que dispone el procesador ARM de la consola, listados de los índices de los registros a utilizar por cada modo de operación de CPU y una referencia al listado de índices a emplear actualmente en función de la modalidad elegida de la CPU. Además de otras abstracciones que encapsulan el uso de máscaras de bits. En otras palabras y empleando vocabulario más simple el código de los registros lo podríamos asimilar con cómo funcionan las plazas de aparcamiento de las grandes ciudades. Tenemos un listado con todas las plazas de la ciudad. Pero no todas pueden ser usadas indiscriminadamente, sino que su uso está sujeto a condiciones. En función de los horarios de fiestas, de ORA o periodos de carga/descarga el aparcamiento priorizará un determinado usuario o ni siquiera lo permitirá. En nuestra analogía: las restricciones de ORA o de carga/descarga serían el equivalente a los modos Irq, Abt... que tienen una serie de plazas reservadas para tales usuarios; mientras que durante los festivos algunos aparcamientos quedan deshabilitados pero no para los usuarios con permisos como la Autoridad pudiesen utilizar dichas plazas para velar de la seguridad, correspondiendo en con el modo Thumb en donde el procesador oculta algunos registros al programa pero siguen estando en el procesador.

El siguiente paso fue el diseño del bus de datos. Y esta fue una cuestión algo más enrevesada: pues el enfoque por el momento es implementar la CPU ARM7TDMI y no la GBA todavía. Por lo que bajo este prisma es necesario adoptar una solución sin atarse todavía a la GBA, una opción más generalista que permita añadir todos los chips de memoria de GBA cuando esté el procesador de ARM hecho y sea fácil cambiar. Consideremos por convención que una dirección del bus de datos tiene la siguiente estructura:

``` verilog
[    Dirección de memoria    ]
[ Índice ][  Desplazamiento  ]
```

Bajo esta asunción, y del mismo modo como sucede con las máscaras de red para el direccionamiento IP, la parte izquierda de la dirección indica a que chip memoria nos referimos y el resto de la dirección es utilizada para direccionar a los contenidos alojados internamente de dicho chip. Podríamos haber previsto mayor flexibilidad al procesador con otras configuraciones más personalizables como ubicar el índice a la derecha, o repartido a lo largo de toda la dirección. Sin embargo, he creído no necesario manejar tal complejidad por las convenciones utilizadas en la GBA. De otro modo, tendríamos mayor throughtput (cuello de botella) evidente por añadir mayor personalización a nivel de estructura hardware en una GBA que no merece la pena considerar.

En cuanto a la implementación del bus de memoria, la responsabilidad del mismo es permitir: 

- Inserción de nuevos módulos de memoria y eliminación de estos.
- Interacción entre CPU y la memoria.
- Direccionamiento a la memoria deseada a acceder. 
- Obtención de propiedades del bus de memoria a las memorias agregadas.
- El acceso a direcciones sin asignar.
- Memorias espejas.

Esto lo conseguimos proporcionando las propiedades del bus a las memorias cuando son añadidas. Para el ejemplo hay una memoria RAM de ejemplo que en los test se utiliza como memoria espeja.

# Referencias

https://documentation-service.arm.com/static/5f8dacc8f86e16515cdb865a
https://documentation-service.arm.com/static/5e8e1323fd977155116a3129
https://users.ece.utexas.edu/~mcdermot/arch/articles/ARM/arm7tdmi_instruction_set_reference.pdf
