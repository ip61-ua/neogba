Hasta 1 de julio.

# Marco teórico

La emulación es un ámbito informático que procura en la medida de lo posible imitar las instrucciones de una máquina en otra para la que hay fórmula fácil de ejecutarlas. Así es cómo podemos lograr ejecutar programas informáticos (software) antiguos para computadoras no recientes en la actualidad. De esta forma podemos disfrutar del software de cuyo hardware resulta de difícil obtención al alcance de los dispositivos actuales. La principal motivación de los programas emuladores son la preservación del software.

La Game Boy Advance es una videoconsola lanzada por la niponesa Nintendo a principios de los 2000 como sucesora de sus portátiles Game Boy. La familia de las portátiles Game Boy tuvo una gran aceptación el mercado por el asentamiento de sagas vídeojuegos reconocibles. En la actualidad ya no se produce este hardware, lo cual supone un reto para la preservación del software (y en concreto del videojuego). Sin un emulador que pudiese ejecutar programas de ese hardware, no sería fácil reproducir las experiencias originales. Obligando a recurrir a imitaciones, copias y recreaciones derivadas que introducen cambios o dificultan su acceso. Bajo esta utopía, para poder ejecutar programas antiguos hoy, tendríamos que constantemente reescribir todo software. Sin embargo, la emulación propone no imitar la programa sino la máquina donde corre. Debido a su popularidad y a la falta mantenimiento, esta línea de consolas se presta frecuentemente a la enseñanza o experimentación informática.
	
Al igual que cualquier programa informático, el emulador está compuesto instrucciones binarias y basadas en un código fuente legible por el programador. El código fuente es todo aquel recurso utilizado para generar el programa final. Así es que, un código fuente puede albergar archivos de texto, configuraciones, automatizaciones y multimedia necesaria. Rara vez es la que un programa no se escriba en un lenguaje de programación. A grandes rasgos, un lenguaje de programación es un conjunto de reglas sintácticas legibles por el humano que sirven para instruir el comportamiento de un hardware. Existen varias clasificaciones para categorizar lenguajes pero llamaremos a los lenguajes de bajo nivel aquellos con mayor acople al hardware como ensamblador de ARM y los de alto nivel que hagan lo contrario como C++. En función del lenguaje y su uso, puede requerir un transpilador, un compilador o un intérprete para preproceasar.

El desarrollo de un emulador implica conocer en profundidad la arquitectura hardware a la que se pretende emular. La GBA alterna entre dos en función del título a cargar. Esta generación sucesora introduce un procesador ARM. El fabricante ARM es uno de los más grandes y recurridos para los dispositivos portátiles como móviles cuotidianos. Los procesadores ARM han ganado la popularidad de hacer menor consumo energético frente a otros competidores. Tanto ARM como intel son marcas importantes para el desrrollo de arquitecturas hardware. En este sentido una arquitectura puede abargar la organización del hardware, conjunto de instrucciones y lógica booleana para la aritmética, tipos de datos y entre otras cuestiones... En concreto, el procesador ARM de la GBA es ARM7TDMI que implementa la 

También será necesario conocer cómo un software habitúa a ser configurado, alojado, gestionado en colaboración en línea a través de un gestor de versiones del programa como git. Este aspecto es vital para gran parte de emuladores porque suelen estar conformados por un equipos de entusiastas voluntarios a mejorar el programa emulador. En esta línea, cabe esperar conocimiento sobre licencia de software.

Los algoritmos son procedimientos que producen salidas a cambio de entradas siguiendo una serie de instrucciones. Son fundamentales para cualquier programa serio y por tanto es recomendable conocer qué son, fórmulas, y el cómputo de complejidades por encima.

Para este trabajo es recomendable conocer los lenguajes de programación de escritorio y de bajo nivel como el lenguaje de programación C++, las arquitecturas de hardware en general y en concreto la arquitectura ARM, la lógica boleana, la videoconsola Game Boy Advance.

# Motivación

La idea de hacer un emulador siempre ha estado ahí desde que he empezado a usarlos. Pensar que algo que requiera técnica pudiese ser divertido de aprender y examinar. Preguntándome cómo se hacen realmente. Hace cuatro años esta idea empezaba como una broma. Sin embargo, cuando me puse a plantear qué ideas hacer la única que vino es la implementar un emulador. En ese punto me quité de la cabeza sobre que fuera una broma y lo consideré como algo serio. El emulador es una pieza que opera a bajo nivel de los ordenadores que siempre me hubiese gustado tratar en algo más en profundidad en la carrera. Además, creo que este TFG puede ser destacado en un CV fácilmente. No todos los días (y más hoy) que haya tocado fundamentos a tan bajo nivel. Pues su realización implica investigación sobre una máquina ya descatalogada e implementación de la especificación de muchas fuentes. Y por supuesto, la optimización de los recursos. 

El objetivo último de este trabajo es aprender. No es el de competir frente a programas ya bien establecidos y con años de experiencia en este ámbito. Sino el planteamiento de este TFG como un reto. No busco reinventar la rueda sino conocerla más a fondo en este símil.

# Estado del arte

En contrucción... ¿Qué contar aquí?

- la arquitectura chip-8 es muy típica para prácticar emulación.
- la gba se presta a educación -> fundamentos -> ensamblador.
- mgba, libreto, https://emulation.gametechwiki.com/index.php/Game_Boy_Advance_emulators y licencias.
- legalidad -> roms, recrear, preservación, piratería.
- caso de uso -> depuración, pruebas, enseñanza.

# Metodología

Vamos a utilizar git como gestor de versiones del proyecto y github como alojamiento del proyecto. Aplicándose también para la memoria. De forma que el tutor pueda acceder cómodamente al trabajo realizado. La memoria es una plantilla de TFG recomendada por la EPS que emplea latex y su compilación a PDF es realizada a través de github actions, localmente o por una imagen Docker que incluye lo necesario para su compilación.

Voy a utilizar el editor de texto GNU Emacs para la programación en c++ así como para la documentación en latex y anotaciones en markdown con sus debidos paquetes para extender funcionalidades a este programa. A la hora de implementar cierta funcionalidad lo haré teniendo de un lado un archivo para ir anotando los pequeños avances que realice durante la sesión. Tengo configurado el editor de tal forma que fuese lo menos necesario salir de este para la realización de mis tareas. De forma que mientras programo puedo escuchar la radio de música, visualizar con un filtro del tema que uso la documentación en PDF a implementar, utilizar un frontend para manejar repositorios git, programar en c++, compilo el programa y pasarle las pruebas mientras hago anotaciones en markdown. Esto es genial para minimizar la fricción del uso y unificarlo utilizando atajos de teclado similares sin salir de la aplicaciones.

Al cabo de varias notas acumuladas, se pasa a la memoria donde se reordeordena y se corrigen faltan. Además de expandir o simplificar el texto según sea el caso y añadir referencias, formato...

El flujo de trabajo para la implementación del emulador consiste en: primero, determinar qué implementar; segundo investigar las especificaciones y restricciones que puedan afectar; tercero, implementar versión naive y experimentación; en cuarto lugar, escribir pruebas para automatizar y garantizar un mínimo funcionamiento y búsqueda de errores; y por útimo, refactoriazar y optimizar. Mientras tanto ir anotando los apartados que considero de revelante interés para la memoria tales como una explicación lo qué he hecho, comparativas entre diferentes versiones, justificación de la aplicación de buenas prácticas. Es siempre preferible escribir test porque automatizan la labor de comprobación del programa sin tener una versión completa del mismo. No obstante, para una mayor profundidad en la inspección del funcinamiento del programa, se recurre al frontend depurador a través de línea de comandos para el acotamiento de fallos.

El código fuente del emulador está escrito en el estándar C++26. A través del uso clangd podemos recibir en el editor de preferencia ayuda y sugerencias estáticas sobre nuestro código. Útil para la prevención de errores. Para las pruebas automatizadas, el proyecto hace uso del framework Google Test. Se ha preferido una simple construcción del proyecto con reglas escritas directamente para make inicialmente con tal de tener ya algo que se pueda ejecutar y probar desde el día uno. En un futuro con tal de extender su portabilidad, se podría implantar un metagenerador de proyectos para ajustarse mejor a la realidad de la programación en C++. Cabe recalcar que el código es automáticamente estilado por otra de las herramientas de clang para seguir en todos el mismo estilo y formato fuente. Siendo estas recomendaciones las de LLVM por su cercanía con el estilo de progrmación en lenguajes modernos. Al estar programando en C++ definiremos que los archivos de cabecera con la extensión hpp y los de implementación cpp.

A la hora de subir los cambios del emulador, el mensaje de confirmación de git será en inglés y prefijado con una abreviatura del tipo de cambio efectuado (refactorización, nuevas funcionalidades, documentación, arreglos...). 

Para la comunicación con el tutor se hace uso de reuniones presenciales, mensajería por correo electrónico, y asignación de fechas por Google Calendar.

# Implementación

## Trabajo previo

Antes de empezar el trabajo en serio, empecé una implementación de prueba. Aquella versión preliminar tenía como objeto de estudiar la viabilidad de la realización del TFG y predendía seguir uns prácticas idomáticas del lenguaje C++. Todo ello mientras me familiarizaba con la forma de realizar las pruebas con el framework y a investigar sobre la consola. En concreto el objetivo fue la implementación de una instrucción que sumara dos números. Ello suponía antes tener toda una infraestructura: Métodos y propiedades de la CPU, bus de memoria y la memoria. Aunque logré que realizara la suma lo cierto es que el código resulte dejaba mucho que desear. Las refactorizaciones al programa eran engorrosas y las prácticas idiomáticas dificultaban la lectura y entendimiento del programa. La lección que aprendí de este experimento es que aplicar los típicos hábitos de programación de alto nivel a uno más bajo era contraproducente. En un emulador buscamos escribir menos y muy óptimo, y evitar la sobrecarga de boilerplate. Por ejemplo, considerar cada registro como una clase o encapsular cada tipo de instrucción como una clase. En este último ejemplo es más propicia a errores. Despachar según el tipo de instrucción y no en instrucción concreta tiene un coste importante dado las pocas optimizaciones que se le puede aplicar. En el prototipo preeliminar definí una clase por cada tipo de instrucción, y que luego esa clase era la encargada de averiguar qué tipo de instrucción era exactamente. Sumado a otros métodos auxiliares de construcción y depuración implicaba para una clase asumir demasiadas responsabilidades. Otra de las cuestiones que motivaron al cambio fue la lentitud de los test que justificaban las pésimas decisiones de optimización. 

Pese a las dificultades, logré implementar una RAM de ejemplo y bus de memoria siguiendo la filosofía de POO. No fue tan costoso de seguir. Esta parte era bastante susceptible de ser implementada de esta forma. Pero sin embargo se notaba cómo un hack al tener que la memoria manejar información sobre sí misma en el bus... Una de las características que fueron curiosas de implementar es la memoria espejo. Siendo que en la memoria persistía una lista y daba igual la dirección de memoria socitada a acceder/modificar que involucraba al mismo offset.

Estos golpes de realidad motivaron a realizar importantes simplificaciones para centrarse más en mejoras que en escribir el código. Llegando averiguar más sobre cómo los emuladores de GBA dispachan la instrucción que toca de formas más óptimas usando tablas LUT frente a bloques switch. Y en paralelo, averiguar un algoritmo para rellenado de esta tabla.

El rumbo era el mismo pero el camino había cambiado. Ante el desconocimiento del gran repertorio de características del lenguaje hacía lento y complicado avanzar, opté por crear una versión lo más naive que, con el paso del tiempo, actualizaría para garantizar una mejor legibilidad de código y prácticas idiomáticas.

Lo primero que implementé fue una estructura básica de la cpu de ARM7TMI como un dos arreglos. Uno era una lista fija con todo el espacio necesario para albergar los 37 registros necesarios en total. Y la segunda servía para indicar cuales de estos registro utilizar. En otras palabras, esta segunda lista contiene solo los índices de los registros que se pudiesen precisar en ese modo. Otra de las implementaciones para este caso fue hacerlo sin la segunda lista y proporcionando un método que computará el índice del registro a interactuar. El problema era hacerlo de este modo resultaba muy complicado y surgían muchos condicionantes a evaluar. Dicho lo cual ralentizaba el rendimiento con branch misprediction (predicción de saltos) de los ordenadores modernos. Este suceso si bien no copiaba listas en listas daba pie a un problema todavía mayor: la falta de predicción y a una gran complejidad ciclomática por cada instrucción. En ese sentido esta implementación es peor porque realiza muchas operaciones por cada vez que nos refiramos a registros, mermando a así el rendimiento. Pudiendo haber 3 registros involucrados, lo cual carece de eficiencia al repetirse el mismo proceso eficiente. En consecuencia, la primera implementación es más oficiente porque en caso de hacerse el cambio de modalidad arm, solo se hace una copia de una lista de elementos que sí sabemos qué son a simple vista. Además esta copia lista a la lista índices actual se hace una vez y solo cuando se pida el cambio de modo. Que resulta en una menor frecuencia que la manipulación de registros.

A continuación añadí algunos métodos para una fácil lectura y escritura del código para la manipulación de registros. Para decir que registros estaban en qué modos del procesador utilicé macros. Las macros son un mecanismo heredado de C para copiar y pegar texto del código fuente mecanismo que más tarde sería remplazado por otro con seguridad de tipos y restricciones. 

Antes de proceder con la reescritura, decidí por implementar siguiendo la documentación los tipos las intrucciones. Aquí el enfoque sería complemente diferente: no hay clases solo funciones auxiliares para el conjunto del set de instrucciones. De modo que si una instrucción necesitase extraer/establecer unos campos o ignorar otros lo pudiese decidir y operando sobre el bits de las instrucción. El problema era poner en marcha este planteamiento porque requiere crear demasiadas funciones muy similares entre sí. Casi siempre son las mismas operaciones con datos de entradas de diferentes. A menudo, plantarse un número prohibitivamente grande de operaciones muy similares entre sí sugiere utilizar algún tipo de metaprogramación con tal de mejorar la mantenibilidad en el futuro y reducir la tasa de error al codificar estos casos. Al igual en el anterior párrafo hice uso de las macros para generar las funciones. Cosa que posteriormente resultó en una refactorización con las plantillas.

Las templates son un recurso de metaprogramación que son evaluados en tiempo de compilación que fueron introducidos en c++. La ventaja de esta característica integrada es una mejor integración con el código respetando el tipado estático. El remplazo de macros por las templates resulto en una mejora de tiempos en las pruebas.

Algunos de los registros son para el acceso a los registros del modo actual, acceder al contador del programa, método para cambio modo y actualizar todo lo necesario de la estructura de la cpu. Los métodos estan en su mayoría están pensados para usarse con lógica boleana así como operadores ~ & | ^ para una mayor flexibilidad de manipulación. Es el ejemplo para la lectura y escritura del registro cpsr. 

En cualquier caso, las pruebas automatizadas han tomado un papel fundamental para ir construyendo un programa paso a paso, comprobando que las cosas funcionen y no haya ninguna letra mal puesta o algo que no esté en su sitio. 

Luego de realizar los cambios, me puse a analizar el método que hace cambia de modo. Resulta que existe toda una ciencia detrás de las optimizaciones del compilador. GCC y CLANG son los dos compiladores más establecidos en el entorno de desarrollo de C++. Y hay que tener en cuenta que no todos producen el mismo binario dado un mismo código fuente. Por ello interesante ver el comportamiento y las optimizaciones aplicadas por distintos comportamientos. Pequeños cambios como pasar de usar un tipo de 64 bits a uno 8 bits puede afectar al rendimiento. 

El método a analizar estaba implementado por medio de un bloque switch y para caso un return del índice de la lista activa por la que cambiar. Pese a que pueda ser una buena idea, realmente el binario obtenido de un compilador u otro. Pudiendo resultar en una especie de LUT o condicionales consecutivas. Para ambas compativas y usando el -O3, GCC ha detectado un patrón y ha transformado el bloque switch tabla de búsqueda a difrencia que clang que dada con una tabla de satos. La versión obtenida por GCC tiene solo un salto condicional. La refactorización que se propone es aprovecharse de la operación de bits para construir el índice de forma que se suma tomando los dos primeros y los dos siguientes desplazados a la derecha a 2. Pero antes si el modo de sistema solicitado es el de sistema devolver inmediato directamente. En consecuencia, logramos una versión con menos restricciones en la es más suceptible a ser mejorada por el compilador. GCC emplea una instrucción cmove encarga en sobreescribir el resultado con 1 si la comparación es igual a 31 (0b11111).

La página godbolt lo pone sencillo para la inspección del ensablador pudiendo combinar flags, compilador y máquina objetivo. Este tipo de prácticas resultan siempre interesantes tratar puesto que cambios simple pueden mejorar la eficiencia del programa. Además notar los cambios en el binario producido por cada campilador y/o cambio en el sistema.

# 2 de julio 

¿qué voy a hacer?
- quitar macros por std::arrays en las instrucciones. (hecho)
  - Por el mismo motivo de siempre, #STOPMACROS.
  - pueden ser evaluadas en tiempo de compilación. 
  - CAMBIOS:
    - Manejo de memoria más simple, sin necesidad de copiar
	- Asignación o fill.
	- complicación en los test -> resuelta con un for mejor.
	- ahora ocupa un registro menos (es fíctício el spsr, por que no está en usr ni sys)
	- reducción de tamaño en uno -> mejor provecho de espacio
	- tarda más con std::array (pasando de 8 a 11 segundos)
    - no puede ser porque array es 0-cost abstraction
	- lo que está pasando es que tarda por que gtest tiene una impresora al comparar arrays que lo ralentiza.
	- si los test son muy lentos, considerar valorar esto assert_true == o recuperar el método de memcmp que había antes par comparar.

- Añadir métodos de lectura y escritura de calquier registro. (mu facil)

# 3 de julio

¿qué voy a hacer?
- me he pasado a un ordenador de torre con debian donde puedo seguir trabanjando con mi metodología con el añadido de verlo en pantalla grande para los errores de c++ (lol).
- implementar instrucciones aritméticas.
  - ADC Add with carry Rd := Rn + Op2 + Carry
  - ADD Add Rd := Rn + Op2
  - AND AND Rd := Rn & Op2 
  - BIC Bit Clear Rd := Rn & ~ Op2 
  - CMN Compare Negative CPSR flags := Rn + Op2
  - CMP Compare CPSR flags := Rn - Op2
  - EOR Exclusive OR Rd := (Rn AND NOT Op2) OR (op2 AND NOT Rn)
  - MOV Move register or constant Rd : = Op2
  - MVN Move negative register Rd := 0xFFFFFFFF EOR Op2
  - ORR OR Rd := Rn OR Op2 
  - RSB Reverse Subtract Rd := Op2 - Rn 
  - RSC Reverse Subtract with Carry Rd := Op2 - Rn - 1 + Carry 
  - SBC Subtract with Carry Rd := Rn - Op2 - 1 + Carry
  - SUB Subtract Rd := Rn - Op2
  - TEQ Test bitwise equality CPSR flags := Rn EOR Op2 
  - TST Test bits CPSR flags := Rn AND Op2

  - ESTOY ENCRONTRANDO DISCREPANCIAS EN LA DOCUMENTACIÓN
  - me he puesto a hacer and
  - he decidido añadir un bit i en fsr.
  - https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf
  - complicación porque hay que anidar mucho o muchas funciones repetidas.
  - lo voy a hacer full naive que posteriormente usar templates o algo para mejorar el código. 
  - operand2 tiene dos formas de operar en función del bit i
    - o es un registro con shift (tipo de shift determinado)
	- o un inmediato rotado por dos
	- por lo tanto operand2 como tal no existe
	- hay casos especiales
	- he tenido que añadir más extractores
	- Operand2 es muy complicado pero es común a todos los data procesing por igual
	- me pongo a hacer una prueba
	- tanto tiempo programando tengo la cabeza como un platillo y no me doy cuenta de que hay que inicializar registro lol.
	- la funcion amr_and funciona pero creo que como vamos a trabajar con lut vamos a necesitar con muchas versiones de modo que quitaremos ifs y ramas incesesarias y utilicemos ifs.
	- la custión aquí es como hacerlo "modular". Según he estado investigando el equipo de mgba lo que hace es construir por partes usando macros. Digamos hay una versión con al S activa y otra sin activar, otra usando el campo operand2 que toca directamente.
	- Este es idóneo al que provecharse. No obstante, hay partes que dependen de como haya ido la anterior. 
	- Recordar que la idea es crear alto rendimiento para hacerlo más realista.
	- Creo que es posible hacer algo así en c++ idomático. En donde realmente lo cambia es en sí el manejo de la operación en sí. (Bueno aunque operand2 tiene su telita) pero es un proceso muy mecánico que siempre será el mismo y lo más importane que tendrá el mismo resultado, sacar un número de operand2 del que podemos operar. Aunque hay caveats porque si el flag s está activo implica actualizar el registro en base a lo ocurrido en la ejecución.
    - por qué he puesto fuera las instrucciones? por no engrasar tanto a la estructura del arm7tdmi	
  - He cambiado el obtenedor de conjuntos de registros de usar una condicional a usar la operación módulo.

# 7 de julio

- La mayor penalización en un emulador es el if.
- La idea cómo construir la LUT es hacerla de tal forma que eliminemos lógica condicional y la remplacemos por la lógica aritmética.
- En bruto, nuestro objetivo es eliminar el típico código if (true) algo.
- Algunas de las opciones barajadas:
  0. Dejarlo con las condicionales. -> Penalización extrema
  1. Escribir a mano todas las combinaciones. Lo cual da bastante puede dar pie a errores tipográfico y código poco de reusable.
  2. Algún mecanismo de metaporgación de plantilla. No me cuadra ninguna cabida de implementación por su rigidez. Este es la solcuión utilizada en mgba con macros bajo c. Lo cual resulta bastante práctico y flexible a prestarse a este tipo de situaciones.
  
  el código inicial es 
  
  ``` c++
  
void neogba::arm_AND(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, imm, rm, operable_operand2{};

  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};
  u8 shift_type, rm_idx;

  bool i{ISA_ARM_FSR_I::get(inst)};
  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};
  bool four, is_special_case;

  if (i) {

    // operand2 is immediate value with shift.

    shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    imm = ISA_ARM_FSR_OPERAND2_IMM::get(inst);

    operable_operand2 =
        (shift_amount == 0) ? imm : ((imm >> shift_amount) | (imm << (32 - shift_amount)));
  } else {

    // operand2 is a register with shift.

    rm_idx = ISA_ARM_FSR_OPERAND2_RM::get(inst);
    rm = cpu->read_active_register(rm_idx);
    shift_type = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst);
    four = ISA_ARM_FSR_OPERAND2_4::get(inst);

    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);

    is_special_case = !four && shift_amount == 0;

    switch (shift_type) {

    case LSL:
      if (is_special_case) {
        operable_operand2 = rm; // LSL #0
      } else {
        operable_operand2 = (shift_amount >= 32) ? 0 : (rm << shift_amount);
      }
      break;

    case LSR:
      if (is_special_case)
        shift_amount = 32; // LSR #0

      operable_operand2 = (shift_amount >= 32) ? 0 : (rm >> shift_amount);
      break;

    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0

      if (shift_amount >= 32) {
        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        if (cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C))
          operable_operand2 = 0x80000000;

        operable_operand2 |= (rm >> 1);
      } else {
        shift_amount %= 32; // 32 = 64 -> rotate 0 bits
        operable_operand2 =
            (shift_amount == 0) ? rm : ((rm >> shift_amount) | (rm << (32 - shift_amount)));
      }
      break;
    }
  }

  u32 res = cpu->read_active_register(rn_idx) & operable_operand2;

  cpu->write_active_register(rd_idx, res);

  if (s)
    cpu->set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V,
                  (res == 0 ? arm7tdmi::Z : 0) | (((res & 0x8000000) != 0) ? arm7tdmi::N : 0));
}
  ```

Y la idea es ir modularizarla. 

- La primera refactorización consistirá en homogenizar el cómputo de operand2 puesto será una cuestión recurrente en operaciones de este tipo. 
  - Para esto vamos llevarnos a funcionalidad aparte. Al estar todo junto, como típica replicación, debemos refactorizar para ver qué trasladar.
  - Ahora queda mucho más claro que hay que pasar por computar operand2 obligatoriamente.
  
  ``` c++
  #include "neogba/arm7tdmi/arm_isa.hpp"

using namespace neogba;

neogba::arm_operand2_result neogba::arm_operand2_compute(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, imm, rm, operable_operand2{};
  u8 shift_type, rm_idx;

  bool i{ISA_ARM_FSR_I::get(inst)};
  bool four, is_special_case;

  if (i) {

    // operand2 is immediate value with shift.

    shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    imm = ISA_ARM_FSR_OPERAND2_IMM::get(inst);

    operable_operand2 =
        (shift_amount == 0) ? imm : ((imm >> shift_amount) | (imm << (32 - shift_amount)));
  } else {

    // operand2 is a register with shift.

    rm_idx = ISA_ARM_FSR_OPERAND2_RM::get(inst);
    rm = cpu->read_active_register(rm_idx);
    shift_type = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst);
    four = ISA_ARM_FSR_OPERAND2_4::get(inst);

    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);

    is_special_case = !four && shift_amount == 0;

    switch (shift_type) {

    case LSL:
      if (is_special_case) {
        operable_operand2 = rm; // LSL #0
      } else {
        operable_operand2 = (shift_amount >= 32) ? 0 : (rm << shift_amount);
      }
      break;

    case LSR:
      if (is_special_case)
        shift_amount = 32; // LSR #0

      operable_operand2 = (shift_amount >= 32) ? 0 : (rm >> shift_amount);
      break;

    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0

      if (shift_amount >= 32) {
        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        if (cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C))
          operable_operand2 = 0x80000000;

        operable_operand2 |= (rm >> 1);
      } else {
        shift_amount %= 32; // 32 = 64 -> rotate 0 bits
        operable_operand2 =
            (shift_amount == 0) ? rm : ((rm >> shift_amount) | (rm << (32 - shift_amount)));
      }
      break;
    }
  }

  return {shift_amount, operable_operand2};
}

void neogba::arm_AND(arm7tdmi* cpu, u32 inst) {
  // u32 operable_operand2{};

  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};

  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};

  auto result{neogba::arm_operand2_compute(cpu, inst)};

  u32 res = cpu->read_active_register(rn_idx) & result.operable_operand2;

  cpu->write_active_register(rd_idx, res);

  if (s)
    cpu->set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V,
                  (res == 0 ? arm7tdmi::Z : 0) | (((res & 0x8000000) != 0) ? arm7tdmi::N : 0));
}
  ```

  - con esto en mente, lo que podemos hacer es otra optimización al código de obtención del valor a operar de operand2, es crear una pequeña tabla lut cogiendo y tomando valores de interés. En otras palabras, vamos a aprovecharnos de la abstracción de los extractores para realocar a nuestra conveniencia e interés un código personalizado que sirva a modo de índice para ubicar la operación concreta a realizar. Esto es plausible debido a la muy definida funcionalidad y acotada combinación. Para he esto he hecho explícito un método para devolver u8 en los extractores del estilo isa_bool.
  - NO NO LO VEO.
  
  
8 de julio

Creo que es necesaria la abstracción de lut. Mucho hablar teoricamente y pero poca prácticticidad.

``` c++

template <std::size_t max_lenght, typename store_t = void*, typename idx_t = neogba::u8,
          typename return_t = void>
struct lut {
private:
  std::array<store_t, max_lenght> storage;

public:
  virtual std::size_t norm_idx(idx_t idx) const;

  store_t get(idx_t idx) const;
  return_t run(idx_t idx, ...) const;

  void put(idx_t idx, store_t what);
  void fill(idx_t idx_base, store_t what, idx_t mask);

  void erase(idx_t idx);

  bool is_empty() const;
  bool is_empty(idx_t idx) const;

  std::size_t length() const;
  std::size_t count_stored(store_t what) const;
};

```

- Me he dado cuenta que un plantilla no debería ir en un archivo separado
- lo he juntado todo.
- he hecho todo a tiempo de compilación.


``` c++
template <std::size_t max_length, typename store_t = void*, typename idx_t = u8,
          typename return_t = void>
class lut {
private:
  std::array<store_t, max_length> storage{};
  constexpr void put(std::size_t raw_idx, store_t what) { storage[raw_idx] = what; }
  constexpr std::size_t fill_recursive(std::size_t base, std::size_t mask, store_t what, bool high,
                                       std::size_t bit = 0) {
    // caso base
    std::size_t shifted{mask >> bit};
    if (shifted == 0)
      return 0;

    // caso recursivo no fork
    bool is_mask_one{(shifted & 0x1u) == 1};
    if (!is_mask_one)
      return fill_recursive(base, mask, what, high, ++bit);

    // caso recursivo branch
    std::size_t exclusive_mask_bit{1u << bit}, exclusive_base_bit{base & (exclusive_mask_bit)};
    bool is_base_zero{exclusive_base_bit == 0}, is_base_one{not is_base_zero}, low{not high};
    u8 count{0};

    if ((high and is_base_zero) or (low and is_base_one)) {
      count = 1;
      base ^= exclusive_base_bit;
    }

    ++bit;

    return count + fill_recursive(base, mask, what, true, bit) +
           fill_recursive(base, mask, what, false, bit);
  }

public:
  constexpr virtual std::size_t norm_idx(idx_t idx) const { return static_cast<std::size_t>(idx); }

  constexpr store_t get(idx_t idx) const { return storage[norm_idx(idx)]; }
  constexpr return_t run(idx_t idx, auto... params) const { return get(idx)(params...); }

  constexpr void fill(idx_t idx, store_t what) { storage[norm_idx(idx)] = what; }
  constexpr std::size_t fill(idx_t idx_base, store_t what, idx_t mask) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};

    return fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }

  constexpr std::size_t length() const { return max_length; };
  constexpr std::size_t count_stored(store_t what) const {
    std::size_t n{};
    for (auto elem : storage)
      if (elem == what)
        n++;
    return n;
  }
};
```

  - Luego me puse a refactorizar el código para una versión branchless el caso de recursivo branch.
  - Pero no tuvo tanto sentido, porque no cubiría la llamada a función
  - Además esto tiene penalización en tiempo de compilación y no en ejecución preferiblemente. O en caso de tenerlo, sería mínimo en ejecución por la naturaleza de la estructura.
  - Vale, me estoy liando. Vamos a hacer naive en caso recursivo branch para ir pasando los test y optimizando. O no porque a quién le importa si es solo una vez.
  - vale ya se lo que estaba pasando y es que el test estaba mal. No seguía la signatura bien. He simplificado lógica.
  - ES MUY IMPORTANTE DEPURAR ANTES QUE HACER PRINTS.
  - mE HE PUESTO AHORA con intentar añadir funciones a la lut. Por que esto es lo deseable, definir un conjunto de operaciones finitas que puedan ser llamadas con similar signatura.
  - A la hora de utilizar funciones el lenguaje emplea todo un sistema moderno funcional. Creamos signatura de función con using.
  - Los lambdas con funciones anónimas y en la actualidad el estándar del c++ da demasiadas oportunidades para usarlas incluso en plantillas.
  - Para garantizar que las pruebas vamos a utilizar lambas que alteres variables del test. Lo cierto es que hay varios tipos de lambdas. Una es preservando con capturas referencias locales de ámbito, pero ello pierde ser una función típica. Es decir deja de ser un puntero crudo como sí pasa en c.
  - interesa hacer un test fácil, comprobar que realmente se ha llamado. Y esto es más típico de mocks en donde comprobamos de forma unitaria a llamada a una dependencia externa falsificando su comportamiento y retorno para registrar que tal llamada sí fue efectiva. sin embargo, vamos a hacer algo más simple y es comprobar que unos valores externos hayan sido modificados.
  - sin embargo, gtest trae un framwwork para mocking.
  - HACER EXPECT CALL.... un poco más enrevisada la sintaxis no es tan directa como en otros frameworks como easy mock en java.
  
# 9 de julio

  - he añadido más test para comprobar cómo usar la lut.
  - he optimizado algunas cosas más. como reemplazar la operación módulo por una máscara.
  - Hay un problema en el método run y es que el reenvío de parámetros a sus repectivas funciones, las copia y no preserva referencias.
  - para solucionar esto debemos utilizar la referencia universal auto&&... params para tratar todos los tipos lvalue o rvalues o mantener de solo lectura. 
  - std::forward<decltype(params)> reenvia y mantiene la naturaleza de todos los tipos empaquetados en params mientras interfamente se trate como lvalue en el ámbido de run. Aunque viene a mantener soluciones recientes de c++ de movimiento.
  - Las llamadas virtuales tienen un coste a asumir. Añaden overhead de indirección.
  - por ello, he replanteado que en lugar de utilizar la derivación de la clase lut, he utilizado la inyección de políticas. Esto es que, hay un parámetro de plantilla que dicta el comportamiento de la lut. De modo que no permita cambio en tiempo de ejecución. Esto adelanta lo máximo posible al tiempo de compilación.
  - Beneficiándose de mayor flexibilidad.
  
  - Ahora que tenemos todo esto funcionando... ¿para qué?
    - bien, creo que es haber tocado esta estructura antes podemos hacernos a la idea los problemas y usabilidad de la misma.
	- métafora: la lut = multiplexor. En el fondo, eficiencia de una estructura depende fuertemente del uso que se le vaya a propiciar.
	- ! all struct are =
	- si pensamos a nivel de hardware, el multiplexor es una estructura perfecta para la búsqueda. Por que es directa!!!
	- Sabe exactamente donde hay un ítem o qué salida dar. O si hay varias que emitan la misma salida.
	- los multiplexores tienen una longitud fija. A no ser que interconectemos uno con otro.
	- lo que buscamos es una abstracción de coste cero que pueda ser ahustada a nuestras necesidades usando plantillas.
	- la lut no es más que un array "vitaminado" con métodos para poner más fácil inserción de elementos y también utilizar un código que sirva a modo índice con el navegar entre opciones. Pero el código que se use puede ser otro al que realmente se utilice. Dejando a conveniencia bien devolver 42, o un número aleatorio, o desaprovechar las entradas de la lut, o idílicamente aprochear para recortar y ajustar los bits de interés de la máscara.
	- otro caso de uso al que se le puede prestar esta implementación es al direccionamiento de memoria. Decidir a qué chip consultar.

  - Así retomando la especificación del cómputo de operand2 podemos ponernos a analizar como aplicarlo al cómputo de operand2.
  - Lo debamos hacer ahora es ver cómo podemos unificar todos las distintas combinaciones.
  - De una operación de procesado de datos y fsr nos interesa conocer su bit i y el campo operand2. Ya ha pasado un tiempo en el que no no acuerdo bien cuales ni cuántos eran. Pero los podemos construir utilizando los extractores.
  - Yo haría la lut tabla basándome en cómo esta hecha la implementación de operand2. 
  - De manera que es un método muy estúpido y mecánico en el explorar en orden las conexiones y bifurcaciones del código.
    1. siendo el bit i el más condicionante en la decisión.
	2. dentro de i = true, shift_amount es un condicionante porque dicta si devolver solo imm o realizar operación de encadenamiento y desplazo.
	
	- Por lo tanto tenemos que 
	  
	  ``` 
	  (lenguaje lógico)
	  shift_amount = rotate == 0
	  
	  i ^ shift_a  -> imm
	  i ^ -shift_a -> ((imm >> shift_amount) | (imm << (32 - shift_amount)))
	  ```

    3. Ahora si el i no es true, vamos a otra parte del código en la que se asume que "operand2 is a register with shift", y es algo más complidaca.
	4. el bit 4 nos dice si es otro registro o es shift_amount. En parte del código donde es realmente dificil hacer una inspección, podemos aplicar otro método y este consiste en ir del final al principio. Siendo que primero tomemos las sentencias finales y visualicemos qué ha hecho falta para llegar a ellas.

	- Por lo tanto tenemos que 
	  
	  ``` 
	  (lenguaje lógico)
	  -i ^ lsl ^ special_case                       -> rm
	  -i ^ lsl ^ -special_case ^ (shift_a >= 32)    -> 0
	  -i ^ lsl ^ -special_case ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^ special_case                       -> (shift_a = 32) // dejar e ir 
	  -i ^ lsr ^ (shift_a >= 32)                    -> 0
	  -i ^ lsr ^ -(shift_a >= 32)                   -> rm >> shift_a
	  -i ^ asr ^ special_case                       -> (shift_a = 32) // dejar e ir
	  -i ^ asr ^ (shift_a >= 32) ^ (rm is neg)      -> 0xffffffff
	  -i ^ asr ^ (shift_a >= 32) ^ -(rm is neg)     -> 0
	  -i ^ asr ^ -(shift_a >= 32)                    -> static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount)
	  ```


    es un proceso similar al diseño y simplificación máquinas de estado finito.
	
	- en este punto me percato que asr puede simplificarse de sobremanera. ¿porqué? porque podemos aprovecharnos del desplazamiento con preservación de signo también para devolver los valores estáticos y con una regla de comprobación mínimos.
	

  originals (r)

	``` c++
	
    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0
      if (shift_amount >= 32) {

        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

	```

moderns (tm)


	``` c++	
    case ASR:
      if (is_special_case) {
        shift_amount = 32; // ASR #0
      }

      operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
      break;

	```

	por lo que:
	
	``` 
	  (lenguaje lógico)
	  -i ^ lsl ^ special_case                       -> rm
	  -i ^ lsl ^ -special_case ^ (shift_a >= 32)    -> 0
	  -i ^ lsl ^ -special_case ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^ special_case                       -> (shift_a = 32) // dejar e ir 
	  -i ^ lsr ^ (shift_a >= 32)                    -> 0
	  -i ^ lsr ^ -(shift_a >= 32)                   -> rm >> shift_a
	  -i ^ asr ^ special_case                       -> (shift_a = 32) // dejar e ir
	  -i ^ asr                                      -> static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
	  -i ^ ror ^ special_case                       ->  |= (rm >> 1)
	  -i ^ ror ^ -special_case ^ (shift_a == 0)     -> rm
	  -i ^ ror ^ -special_case ^ -(shift_a == 0)    -> ((rm >> shift_amount) | (rm << (32 - shift_amount)))
    ```


es complicado, pero ayuda podemos decidir más fácilmente cómo optimizar y simplificar.

   - lo cierto es que is_special_case{!four && shift_amount == 0}; y 
    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);
    no lo pone nada fácil en codificar.
	
   - sin embargo, pensemos por un momento: el bit 4 es clave !!! y partir de ahí podemos sacar si usar una u otra fórmula de obtención del numérico.
   - en paralelo tenemos shift_type que siempre está en el mismo sitio y en ese sentido no hay tanto problema.
   - el problema tocho viene por el bit 4 que enfunción de este deberemos hacer un doble aplanamiento. Por que intercede si considerar 5 bits o 4 cuatro. Volviéndose peligroso al tener que que crear por cuatro casos de rotación por 2 diferentes implementaciones de extrema semejanza. 
   - esta posiblemente sea una de las grandes desventajas de un código tan corto e hiperespecializado: duplicación de código.
   - sin embargo obtenemos un código con una única responsabilidad. 
   
   
   una idea que se me ocurre de atacar esto es añadiendo una indirección. porque piensa en que tú el fondo lo que te intersa tener para luego en las rotaciones el shift_amount y special_case. 
   AHora pensándolo mejor, la dirección es casi obligatoria. Solo lo es para el caso de cuando el bit 4 esté activo por que recuperará un dato de la cpu. sin embargo aquí la cpu es un ""ente"" ajeno del que es IMPOSIBLE conocer de antemano que devolverá ese read ya que depende de un contexto y estados no relativos a la instrucción. 
   
   Además el tema de bits es lo menos que sea 5 o 4. si solo fuera ese el problema es que sería relativamente sencillo acotar una solución que proporcionase un número. De algún u otro modo, el read nos dificulta el paso al aplanamiento.
   
   como ya hemos dicho en el shift_type hay una serie bien ubicada y sus valores son comprendidos entre límites precisos.

   Pero hemos de percatarnos de un dato de vital transcendencia que no podemos pasar por alto y es que todo special case será con el bit 4 apagado!! Esto quiere decir que el caso especial solo será cuando trabajemos con shift amount es decir cuando bit 4 sea 0 y shift amount sea 0 también.
   
   Desde este nuevo prisma si es posible asumir ciertas simplificaciones.
	
	```   	  
	  (lenguaje lógico)
	   i ^  (rotate == 0)                -> imm
	   i ^ -(rotate == 0)                -> ((imm >> shift_amount) | (imm << (32 - shift_amount)))
	  -i ^ lsl ^ -4 ^  (shift_a == 0)    -> rm
	  -i ^ lsr ^ -4 ^  (shift_a == 0)    -> (shift_a = 32) ^ operand2 = 0 
	  -i ^ asr ^ -4 ^  (shift_a == 0)    -> (shift_a = 32) ^ operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> 31);
	  -i ^ ror ^ -4 ^  (shift_a == 0)    -> comprobar C ^ |= (rm >> 1)
	  -i ^ lsl ^  4 ^  (shift_a >= 32)   -> 0
	  -i ^ lsl ^  4 ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^  4 ^  (shift_a >= 32)   -> 0
	  -i ^ lsr ^  4 ^ -(shift_a >= 32)   -> rm >> shift_a
	  -i ^ asr ^  4                      -> static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
	  -i ^ ror ^  4 ^  (shift_a == 0)    -> rm
	  -i ^ ror ^  4 ^ -(shift_a == 0)    -> ((rm >> shift_amount) | (rm << (32 - shift_amount)))
    ```

# 10 de julio.

  - nos fijamos en los bits de control y no en los datos. 
  - ojo: si cuando es 0 shift_a y es -4 -> casos especiales. 
  - podemos anticipar el valor de shift_a para casos especiales
  - creo ha llegado de usar el papel.

  - POR PASOS

| Operación                              | I |
|----------------------------------------|---|
| operand2 is immediate value with shift | 1 |
| operand2 is a register with shift      | 0 |

| Operación                                    | I | rotate |
|----------------------------------------------|---|--------|
| imm                                          | 1 | 0      |
| `((imm >> rotate) | (imm << (32 - rotate)))` | 1 | not 0  |
| operand2 is a register with shift            | 0 | x      |

| Operación                                          | I | rotate | bit 4 |
|----------------------------------------------------|---|--------|-------|
| imm                                                | 1 | 0      | x     |
| `((imm >> rotate) | (imm << (32 - rotate)))`       | 1 | not    | x     |
| operand2 is a register with shift (`shift_amount`) | 0 | x      | 0     |
| operand2 is a register with shift (rs)             | 0 | x      | 1     |

| Operación                                          | I | rotate | bit 4 | `shift_amount` |
|----------------------------------------------------|---|--------|-------|----------------|
| imm                                                | 1 | 0      | x     | x              |
| `((imm >> rotate) | (imm << (32 - rotate)))`       | 1 | not    | x     | x              |
| operand2 is a register with shift (`shift_amount`) | 0 | x      | 0     | not 0          |
| operand2 is a register with shift (special case)   | 0 | x      | 0     | 0              |
| operand2 is a register with shift (rs)             | 0 | x      | 1     | x              |

| Operación                                                     | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|---------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                           | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                  | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                             | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                              | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case) | 0 | x      | 0     | 0              | ASR          |
| `(arm7tdmi::C) ? 0x80000000 : 0 | (rm >> 1)`                  | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | ROR          |
	
| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

	
| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

aquí estoy observando que el shift_amount del extractor da un u8 que en realidad es un numero de 5 bit (no el registro rs). Por lo tanto sí bit 4 es 0 el número de shift amount jamás podrá ser superior a 31 por su limitación de base binaria y en caso de superarse desbordaría para 32. Así que naturalmente no tiene sentido comprobar que un número es mayor que otro cuando el primero no requiera más bits que el segundo a compararse. Esto induce a que podemos hacer una temprana detección del shiftamoutn por el bit 4 y evitar las comprobaciones de límites con el hallazgo de mínimos y si sera mayor o igual que 32 porque serán ciclos susceptibles a ahorrarse con motivo de la optimización.

| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not 0  | x     | x              | x            |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| rm << `shift_amount`                                                         | 0 | x      | 0     | not 0          | LSL          |
| rm >> `shift_amount`                                                         | 0 | x      | 0     | not 0          | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x      | 0     | not 0          | ASR          |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x      | 0     | not 0          | ROR          |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

Ante este escenario poco podemos averiguar que valor habrá en rs del que posteriormente solo emplean los 8 bits primeros. Esto como ya hemos dicho antes, depende del estado de la cpu que atraviese la cpu por ese momento. Y por tanto poca optimización podemos realizar.

Una vez ya hecho pedazos la función de operand2, lo complicado es ahora determinar los índices que ocuparán las funciones dentro de la lut. Esta tarea no parece ser fácil tampoco. Pero, como todo, hay verlo sobre el papel. Lo cierto es que la lut que tenemos, tendremos una penalización muy grande de espacio y por tanto peor caché y consecuentemente rendimiento bajo. esto es porque tenemos varios valores que no son unos o ceros. Y mayor agravante si consideramos que solo tenemos 14 casos. Los bits necesarios para capturar esos catorce casos son 4. Aquí surge otro reto.

Vayamos por partes. Razonemos un poco sobre lo que hay sobre la mesa: tenemos que el campo rotate se entremezcla con `shift_amount` siendo que ocupen 4 y 5 bits en el mismo espacio, tenemos que el tipo de shift ocupa 2 bits irremediablemente. Luego no hay que confuncir rs con `shift_amount`. El bit i es un buen distintivo.

Lo que podemos hacer es comprimir los valores del normalizador. Los números largos pasan a valer un bit. Esto que que para los únicos casos donde neguemos no hay interferencias con otros valores. Dando lugar a esta tabla

| n  | Operación                                                                    | I | rotate != 0 | bit 4 | `shift_amount` != 0 | `shift_type` |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 0  | imm                                                                          | 1 | 0           | x     | x                   | x            |
| 1  | `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1           | x     | x                   | x            |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 2  | rm << `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSL          |
| 3  | rm >> `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSR          |
| 4  | `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x           | 0     | 1                   | ASR          |
| 5  | `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x           | 0     | 1                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 6  | rm (special case)                                                            | 0 | x           | 0     | 0                   | LSL          |
| 7  | 0 (special case)                                                             | 0 | x           | 0     | 0                   | LSR          |
| 8  | `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x           | 0     | 0                   | ASR          |
| 9  | `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x           | 0     | 0                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 10 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSL          |
| 11 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSR          |
| 12 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ASR          |
| 13 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ROR          |

En tal caso ahora podemos juntar rotate con bit 4 e interpretar en conjunto con el bit I. Esto lo podemos hacer porque justo para los casos en donde I sea 0 rotate no se considera.


| Operación                                                                    | I | rotate != 0 v bit 4 | `shift_amount` != 0 | `shift_type` |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| imm                                                                          | 1 | 0                   | x                   | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1                   | x                   | x            |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm << `shift_amount`                                                         | 0 | 0                   | 1                   | LSL          |
| rm >> `shift_amount`                                                         | 0 | 0                   | 1                   | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | 0                   | 1                   | ASR          |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | 0                   | 1                   | ROR          |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm (special case)                                                            | 0 | 0                   | 0                   | LSL          |
| 0 (special case)                                                             | 0 | 0                   | 0                   | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | 0                   | 0                   | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | 0                   | 0                   | ROR          |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | ROR          |

Pero sin embargo debamos, reconsiderar rehacer la simplificación tomando las expansiones de los símbolos ROR, LSL...

| Operación                                                                    | I | rotate != 0 v bit 4 | `shift_amount` != 0 | `shift_type` |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| imm                                                                          | 1 | 0                   | x                   | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1                   | x                   | x            |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm << `shift_amount`                                                         | 0 | 0                   | 1                   | 00           |
| rm >> `shift_amount`                                                         | 0 | 0                   | 1                   | 01           |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | 0                   | 1                   | 10           |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | 0                   | 1                   | 11           |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm (special case)                                                            | 0 | 0                   | 0                   | 00           |
| 0 (special case)                                                             | 0 | 0                   | 0                   | 01           |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | 0                   | 0                   | 10           |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | 0                   | 0                   | 11           |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 00           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 01           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 10           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 11           |

ESTO ES MUY TOP.

ES MUY IMPORTANTE: PONER N

| n  | Operación                                                                    | I | rotate != 0 | bit 4 | `shift_amount` != 0 | `shift_type` |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 0  | rm << `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSL          |
| 1  | rm >> `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSR          |
| 2  | `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x           | 0     | 1                   | ASR          |
| 3  | `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x           | 0     | 1                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 4  | rm (special case)                                                            | 0 | x           | 0     | 0                   | LSL          |
| 5  | 0 (special case)                                                             | 0 | x           | 0     | 0                   | LSR          |
| 6  | `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x           | 0     | 0                   | ASR          |
| 7  | `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x           | 0     | 0                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 8  | imm                                                                          | 1 | 0           | x     | x                   | x            |
| 9  | `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1           | x     | x                   | x            |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 10 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSL          |
| 11 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSR          |
| 12 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ASR          |
| 13 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ROR          |

¡SON MAPAS DE Mapas de Karnaugh! (ni me acordaba de FC)

Si organizamos, a conveniencia...
Podemos idenficar que I v bit4 -> 1 para todo n tal que n3 = 1. Es decir, I v b4 -> [8, 16] // 1xxx
Para n2 será 1 si I v (-(r != 0) ^ (s != 0))
Para n1 será -I ^ t1
Para n0 será ((r != 0) ^ I) v (t0 ^ -I)

| n    | Operación                                   | I v b4 | I v (-(r != 0) ^ (s != 0)) | I | r != 0 | b4 | `s` != 0 | `t` |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 0000 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 00  |
| 0001 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 01  |
| 0010 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 10  |
| 0011 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 0100 | `arm_operand2_compute_i0_40_shiftanot0_LSL` | 0      | 1                          | 0 | x      | 0  | 0        | 00  |
| 0101 | `arm_operand2_compute_i0_40_shiftanot0_LSR` | 0      | 1                          | 0 | x      | 0  | 0        | 01  |
| 0110 | `arm_operand2_compute_i0_40_shiftanot0_ASR` | 0      | 1                          | 0 | x      | 0  | 0        | 10  |
| 0111 | `arm_operand2_compute_i0_40_shiftanot0_ROR` | 0      | 1                          | 0 | x      | 0  | 0        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 1000 | `arm_operand2_compute_i0_41_LSL`            | 1      | 0                          | 0 | x      | 1  | x        | 00  |
| 1001 | `arm_operand2_compute_i0_41_LSR`            | 1      | 0                          | 0 | x      | 1  | x        | 01  |
| 1010 | `arm_operand2_compute_i0_41_ASR`            | 1      | 0                          | 0 | x      | 1  | x        | 10  |
| 1011 | `arm_operand2_compute_i0_41_ROR`            | 1      | 0                          | 0 | x      | 1  | x        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 1100 | `arm_operand2_compute_i1_rotate0`           | 1      | 1                          | 1 | 0      | x  | x        | x   |
| 1101 | `arm_operand2_compute_i1_rotatenot0`        | 1      | 1                          | 1 | 1      | x  | x        | x   |

# 17 de julio.

Hoy quiero implementar todas las lógicas.
Pero antes quiero perfeccionar mi and para que actualice los el cpsr flags como toque.
El resto de operaciones creo que será coser y cantar.
Cambiar alguna cosita pero creo que sera fácil.
Lo importante ahora es ver exactamente qué hace la operación y qué implicaciones tiene en los cpsr flags.

es decir vamos a ver cómo se activan V y C en cpsr.
los otros dos son fáciles.

Lo cierto es que viendo la estructura que devuelven las instrucciones creo que hace falta la necesidad de un campo para carry_out. Aunque entiendo de mi yo del pasado para devolver el shift amount, lo cierto es que puede no tener las mismas implicaciones para todos los casos y resulta absurdo tener una lut y luego en concretar un qué hacer hiperespecializado... Pasando por comprobaciones muy similares y añadiendo mayor carga de overhead.

Estoy comprobando que la mantenibilidad es muy baja. Por todas las cosas que hay que cambiar.
Este proyecto https://github.com/nba-emu/NanoBoyAdvance/blob/master/src/nba/src/arm/handlers/handler32.inl una vez más demuestra lo fácilmente descriptivo que es c++ con las plantillas. 

``` c++
  int carry = state.cpsr.f.c;
  u32 op1;
  u32 op2;

  pipe.access = Access::Code | Access::Sequential;

  if constexpr (immediate) {
    int value = instruction & 0xFF;
    int shift = ((instruction >> 8) & 0xF) * 2;

    if (shift != 0) {
      carry = (value >> (shift - 1)) & 1;
      op2   = (value >> shift) | (value << (32 - shift));
    } else {
      op2 = value;
    }

    op1 = GetReg(reg_op1);
  } else {
    u32 shift;

    if constexpr (shift_imm) {
      shift = (instruction >> 7) & 0x1F;
    } else {
      shift = GetReg((instruction >> 8) & 0xF);
      state.r15 += 4;
      bus.Idle();

      pipe.access = Access::Code | Access::Nonsequential;
       }

    op1 = GetReg(reg_op1);
    op2 = GetReg(reg_op2);

    DoShift(shift_type, op2, shift, carry, shift_imm);
  }
```


claro, con este código de así concentramos todo en uno.

``` c++
template <bool a> int get_operand2(int b) { return a ? 1 : b; }
auto v = get_operand2<true>; // es un int(*)(int)
auto b = v(2);               // es un int
```

vale, pensaba era más simple pero no. Hay faena por hacer. Creo que hacerlo de esta forma centralizará y formentará la mantenibilidad. Reducirneod incosistencias y duplicidad de código.

Vale en esta nueva versión he tomado en cuenta el carry y todos los edge cases. Esto posiblemente dé para otra lut y utilizar karnaugh para simplificar saltos ifs, pero de momento hay que tener algo funcando, pero me ha jodido el carry. Creo que es una idea muy certera que pueda llevarse a cabo para optimizar y volver a las luts con karnaugh.

De momento vamos tirando así. Cons ifs. 

He "estilizado" el código para hacer más idiomático.

Yo creo que esto lo dejamos aparcado para seguir con las instrucciones.


The condition codes in the CPSR may be preserved or updated as a result of this instruction,
according to the value of the S bit in the instruction.

Certain operations (TST, TEQ, CMP, CMN) do not write the result to Rd. They are used only to
perform tests and to set the condition codes on the result and always have the S bit set.

The logical operations (AND, EOR, TST, TEQ, ORR, MOV, BIC, MVN) perform the logical action on all
corresponding bits of the operand or operands to produce the result. If the S bit is set (and Rd
is not R15, see below) the V flag in the CPSR will be unaffected, the C flag will be set to the
carry out from the barrel shifter (or preserved when the shift operation is LSL #0), the Z flag
will be set if and only if the result is all zeros, and the N flag will be set to the logical
value of bit 31 of the result.

logical -> -update(V)
(S ^ -r15) > -update
-S v r15 > update
	
<<< aquí veo un potencial comportamiento común. Las lógicas no tocan V ni aunque lo tengan S. Podemos de alguna forma estandarizar este comportamiento para toda lógica que se meta.
	
The arithmetic operations (SUB, RSB, ADD, ADC, SBC, RSC, CMP, CMN) treat each
operand as a 32 bit integer (either unsigned or 2’s complement signed, the two are
equivalent). If the S bit is set (and Rd is not R15) the V flag in the CPSR will be set if
an overflow occurs into bit 31 of the result; this may be ignored if the operands were
considered unsigned, but warns of a possible error if the operands were 2’s


 complement signed. The C flag will be set to the carry out of bit 31 of the ALU, the Z
flag will be set if and only if the result was zero, and the N flag will be set to the value
of bit 31 of the result (indicating a negative result if the operands are considered to be
2’s complement signed).

<<< no obstante hay cosas que comparten en común. como el hecho de proceder a actualizar las banderas. ¿Estás pensando en plantillas? yo también.

If R15 (the PC) is used as an operand in a data processing instruction the register is
used directly.
The PC value will be the address of the instruction, plus 8 or 12 bytes due to instruction
prefetching. If the shift amount is specified in the instruction, the PC will be 8 bytes
ahead. If a register is used to specify the shift amount the PC will be 12 bytes ahead.

<<< esto es importante: PC cambia. 

If R15 (the PC) is used as an operand in a data processing instruction the register is
used directly.
The PC value will be the address of the instruction, plus 8 or 12 bytes due to instruction
prefetching. If the shift amount is specified in the instruction, the PC will be 8 bytes
ahead. If a register is used to specify the shift amount the PC will be 12 bytes ahead.



4.5.6 TEQ, TST, CMP and CMN opcodes
Note
TEQ, TST, CMP and CMN do not write the result of their operation but do set flags in
the CPSR. An assembler should always set the S flag for these instructions even if this
is not specified in the mnemonic.
The TEQP form of the TEQ instruction used in earlier ARM processors must not be
used: the PSR transfer operations should be used instead.
The action of TEQP in the ARM7TDMI-S is to move SPSR_mode to the CPSR if the
processor is in a privileged mode and to do nothing if in User mode.

<<< lo lógico vaya.

de momento voy a montar una estructura de plantillas que sirva para definir qué instrucción es cada cosa y minimizar duplicidades y errores en común. Luego a partir de ahí vamos perfeccionando.
Mi planteamiento inicial es crear una común que acepte un lambda donde haga de por sí la operación solicitada y otro lambda para la actualización de bits. 
SIn embargo, creo que el lambda es lo más bobo... bueno no, en la común creo que sí tiene sentido... No mejor no, no deleguemos más trabajo al compilador. Vamos a evitarle a toda costa la posible indirección del salto.
Entonces la común tendrá un funcionamiento talque primero coja todos los operandos, llame para obtener operand2, operación en cuestión definida por el lambda y luego un if constexpr (caso) para qué actualizar o no actualizar.
Esto último nos puede dar flexibilidad para decidir qué considerar en la futura lut que aglutine todas las operaciones y podamos saltar directamente a ejecutar al sitio que interese con los efectos colaterales que nos interese.

# 18 de julio

He llegado a la conclusión de que es mejor definir un conjunto finito en lugar de dar indirección. De modo que la prioridad para optimizar código con lut sea:

1. Es un conjunto de valores muy concretos? Entonces plantilla y en tiempo de compilación handlear todo eso. Abstraiga los valores concretos a tiempo de compilación
- Vale para cualquier cosa: tipo receta (todo es igual pero cambia una parte solo, lambdas) 

2. Es una función que puede ser utilizada a convenienza múltiples veces? lambda.
- lo recomendable es que el compilador sea capaz de hacerle el inline si es una función simplona.

3. es un valor demasiado grande? quizás podría ser karnaugh pero es mejor simplicarlo lógicamente, como por ejemplo trabajar algo_grande != 0. O dividirlo en varias variables que ayuden a identificar. En otro caso pasar al siguiente.

4. es un valor demasiado grande y hay indirección para conocerlo? Esto es que hay un valor que solo se conoce en tiempo de ejecución y compilación. Por lo tanto aquí no podemos optimizar nada. Toca pasar por el aro y aguardar para que el compilador haga su faena muy bien.

5. Si después de todo puedes ver que hay patrón que se repite, quizás sea indicativo para revisar y abstraer más variables. Pero esto es solo recomendable en fases muy estables y consolidades o con una batería de prueba demasiado exhaustiva.

Entonces creo que tomar en cuenta que hay una plantilla común no es lo más adecuado. Sí bien es cierto que hay código que estará en ambas, lo cierto es que es muy minúsculo y no prohibitivo. No derivaremos y haremos clases de funciones concretas.

Además de que si lo pensamos bien, el conjunto de operaciones no es tanto. `arm_fsr_opcode` solo tiene 16 valores posibles. Y no creo que vaya necesariamente poner un lambda. Precisamente ya el mero echo de que tengamos bien definido este enum `arm_fsr_opcode` es un indicativo que es finito. Un lambda puede llegar agregar indirección. pero esa decisión la delegamos al compilador si hacer inline o no. Propongo que la plantilla en tiempos de compilación evalúe el trozo que le interese poner en hueco de la operación.

Esto tiene otra ventaja y es que podemos despreocuparnos de la ventana de contexto del lambda. Ampliándola a toda la plantilla y sin "paso de parámetros" con referencia ni punteros. Lo cierto que es que no tenemos que definir qué parámetros irán en el lmanda y omitimos el rollazo de cambiarlo de posición porque lol no he considerado un edge case entre las 16 opciones.

Otra cuestión que voy aprovechar es refactorizar `enum` para hacer servir `enum class`. Esto se debe principalmente a aplicar buenas prácticas de programación del lenguaje y hacer lo más idiomático.

hecho. 

Se me ocurre mejor juntarlo todo en uno y decir en tiempo de compilación su es uno u otro (lógico o aritmético).

Esto es una barbaridad de rápido. Y todo muy práctico a hacer refactors ad hoc al vuelo. => esto es que me pongo a implementar los primeros y de repente veo que hay un caso especial que ignora o lo que sea, y es muy directo a modificar una parte solo.

He decidido en añadir variables para conocer los shift de los bits de interés del cpsr.


Ya tengo esto, algo básico con lo que poder trabajar cómodamente e ir aplicando mejoras conforme vea.
Ahora voy a ver la especificación y ver que pasa.

``` c++

template <bool s, arm_fsr_opcode opcode> void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {
  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};

  // Retrieve values
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};
  auto rd_idx{ISA_ARM_FSR_RD::get(inst)};

  u32 c_in = (cpu.read_cpsr() & arm7tdmi::C) ? 1 : 0;
  u32 op1;
  if constexpr (opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2_lut.run(inst, cpu, inst)};
  u32 res{};

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST) {
    res = op1 & op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ) {
    res = op1 ^ op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP) {
    res = op1 - op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::RSB) {
    res = op2.result - op1;
  } else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN) {
    res = op1 + op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::ADC) {
    res = op1 + op2.result + c_in;
  } else if constexpr (opcode == arm_fsr_opcode::SBC) {
    res = op1 - op2.result + c_in - 1;
  } else if constexpr (opcode == arm_fsr_opcode::RSC) {
    res = op2.result - op1 + c_in - 1;
  } else if constexpr (opcode == arm_fsr_opcode::ORR) {
    res = op1 | op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MOV) {
    res = op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::BIC) {
    res = op1 & ~op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MVN) {
    res = ~op2.result;
  }

  // write back the result
  if constexpr (can_write_rd) {
    cpu.write_active_register(rd_idx, res);
  }

  // Side effects
  if constexpr (s) {
    auto z{res == 0 ? arm7tdmi::Z : 0};
    auto n{(res & 0x80000000) != 0 ? arm7tdmi::N : 0};
    auto v{rd_idx == pc ? 0 /* update logic */ : cpu.read_cpsr() & arm7tdmi::V};

    cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | v);
  }
}

```

Esto nos dice la especificación.

The logical operations (AND, EOR, TST, TEQ, ORR, MOV, BIC, MVN) perform the logical action on all
corresponding bits of the operand or operands to produce the result. If the S bit is set (and Rd
is not R15, see below) the V flag in the CPSR will be unaffected, the C flag will be set to the
carry out from the barrel shifter (or preserved when the shift operation is LSL #0), the Z flag
will be set if and only if the result is all zeros, and the N flag will be set to the logical
value of bit 31 of the result.

<<<
Aquí destacamos que:

- las lógicas tienen un tratamiento especial.
- Siendo S := bit s activo, R := rd es 15, F := actualiza banderas
  - S ^ -R -> F
  
- V = default
- C = shift Barrel
- N = 80...
- Z = 00...

<<<

The arithmetic operations (SUB, RSB, ADD, ADC, SBC, RSC, CMP, CMN) treat each
operand as a 32 bit integer (either unsigned or 2’s complement signed, the two are
equivalent). If the S bit is set (and Rd is not R15) the V flag in the CPSR will be set if
an overflow occurs into bit 31 of the result; this may be ignored if the operands were
considered unsigned, but warns of a possible error if the operands were 2’s complement signed. 
The C flag will be set to the carry out of bit 31 of the ALU, the Z flag will be set if and 
only if the result was zero, and the N flag will be set to the value of bit 31 of the result 
(indicating a negative result if the operands are considered to be 2’s complement signed).

<<<
Aquí destacamos que:

- las arithmetics tienen un tratamiento especial.
- ojo con signo y sin signo.
- S ^ -R -> F
  
- V = over 31
- C = cout Alu
- N = 80...
- Z = 00...
<<<

Bien, con esta info que podríamos considerar efectuar los siguientes cambios. Vemos claramente que la relación con la variable lógica que definimos antes R tiene mucho que ver. Rd es un campo de locación fija dentro del campo de instrucción. Esto es que no se mueve y por ende estará en la misma posición siempre. El valor de r15 se codifica como 1111 por lo que podemos identificar fácilmente con un operador and dado que solo nos importa el índice y no el contenido de r15.

con el simulador jarmemu, https://cpulator.01xz.net/?sys=arm (más preciso)

``` assembly
.global _start
.text
_start:
  @ Beginning of the program
  mov r2, #16
  mov r5, #0x80000000
  mov r6, #1
  mov r2, #4
  ands pc, r5, r2 % es legal que s esté habilitado?
  mov r2, #2
  mov r2, #2
  mov r2, #2
  mov r2, #2
  mov r2, #2
  ands r2, r5, r2
```

ejercicio 1

`and pc, r5, r2` = `0xe005f002` = `1110 0000 0000 0101 1111 0000 0000 0010`

| 1110      | 00  | 0 | 0000   | 0 | 0101 | 1111 | 0000 0000 0010 |
|-----------|-----|---|--------|---|------|------|----------------|
| condición | lol | I | opcode | S | r5   | pc   | r2             |

 ----????....====!!!!AAAAçççç
`11100000000001011111000000000010`

ejercicio 2

`ands pc, r5, r2` = `0xe015f002` = `1110 0000 0001 0101 1111 0000 0000 0010`

| 1110      | 00  | 0 | 0000   | 1 | 0101 | 1111 | 0000 0000 0010 |
|-----------|-----|---|--------|---|------|------|----------------|
| condición | lol | I | opcode | S | r5   | pc   | r2             |

 ----????....====!!!!AAAAçççç
`11100000000101011111000000000010`


Vale, otro comportamiento que podemos optimizar es delegar la recuperación del valor de c_in a la función de cómputo de operand2.
¿Por qué?
Bueno en realidad, en la base del código actual hacemos esta recuperación dos veces cuando no es necesario.
Una operación de procesamiento de datos efectúa esta recuperación 

``` c++
u32 c_in = (cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT;
```

pero dentro de la lut de operands2 llevamos a cabo otra recuperación.

``` c++
template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = 0,
          arm_shift_type shift_type = arm_shift_type::LSL>
arm_operand2_result arm_operand2_generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>(cpu.is_cpsr(arm7tdmi::C, arm7tdmi::C))};
```

sabiendo que operand2 es un paso obligatorio para toda operación de ALU, podemos evitar duplicidades y recuperar del generador direcamente.
Es una tontería así de grande pero cada cosa importa.


<<<
- las lógicas tienen un tratamiento especial.
- V = default
- C = shift Barrel
- N = 80...
- Z = 00...
<<<

<<<
- las arithmetics tienen un tratamiento especial.
- V = over 31
- C = cout Alu
- N = 80...
- Z = 00...
<<<


Podemos aprovechar que expandir el resultado a 64 bits en lugar de 32 para y así detectar más fácil el efecto overflow.

Vale.

Bueno ya ha es otro día.

# 19 de julio.

España juega la mundial contra la Argentina. ¡Qué gane España!
Se palpa un ambiente de poca división que recientemente no se ve.
Aunque no se muy futbolero, considero que esto es muy positivo.
Y más si vemos el contexto de crispación, escándalos y desastres en los últimos tiempos.
A ver si sale la segunda estrella...

Estoy mirando en optimizar el código de generación de instrucciones. He implementado siguiendo la instruccón que recupere el spsr al cpsr si el destino es 15 según como se indica en la documentación:

``` c++
if constexpr (rd_pc) 
	cpu.write_cpsr(cpu.read_spsr());


```

"When Rd is a register other than R15, the condition code flags in the CPSR may be
updated from the ALU flags as described above.
When Rd is R15 and the S flag in the instruction is not set the result of the operation is
placed in R15 and the CPSR is unaffected.
When Rd is R15 and the S flag is set the result of the operation is placed in R15 and
the SPSR corresponding to the current mode is moved to the CPSR. This allows state
changes which atomically restore both PC and CPSR. This form of instruction should
not be used in User mode."

He implementado los efectos colaterales para grabar en cpsr diferenciando si sea lógica o no sencillamente. 
En las aritméticas, hay un error en considerar en cual sea el primer operando porque se reviertes para algunas operaciones.
Por lo mi propuesta inicial fue hacer un intercambio de variables para ese caso. Sin embargo, ví la oportunidad de reducir el código del if de operaciones, si realizacemos el intercambio antes de efectuar la operación y después de obtener los operandos 1 y 2. Mi planteamineto inicial fue 

``` c++

  if constexpr (is_inverted_sub) { // a^b^b = a <-> https://youtube.com/watch?v=4KdvcQKNfbQ
    op1 ^= op2.result;
    op2.result ^= op1;
    op1 ^= op2.result;
  }

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP ||
                     opcode == arm_fsr_opcode::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == arm_fsr_opcode::SBC || opcode == arm_fsr_opcode::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == arm_fsr_opcode::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MOV)
    res = op2.result;
  else if constexpr (opcode == arm_fsr_opcode::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MVN)
    res = ~op2.result;

```

aplicando la propiedad xor de memoria que recordé de un vídeo en el que no se podía utilizar una variable auxiliar. Sin embargo, esto queda en una curiosidad más en que en una funcionalidad, existe la función std::swap que en teoría es mejor porque delega la tarea al compilador el método a elegir para dar el cambiazo de dos variables de formas fáciles. Si vemos el código, es casi un hack porque es literalmente cambiar lo que toca op1 y op2.result para evitar cambios mayores. Al margen de la propiedad, he aplicado el std::swap para más idiomatez.

Al margen de esto, esto ha permitido agrupar algo más el bloque de perform operation siendo que ahora no hay accciones que hagan lo mismo escritas por mi a mano.

Ya desde aquí estaba servido el manejo de bits llegando a optar por evitar desplazar innecesariamente o hacer suposiciones o hacer los cálculos parciales para completarlos para que puedan ser alterados a conveniencia. Este último caso es sobre todo para el efecto colateral de las aritméticas cuando s y por si la operación efectuada no es una suma que invierta las variables c y v computados parcialmente y luego aplicar lo mismo para cualquier caso de aritmética.

``` c++
        // another meta template info
        constexpr auto is_sum{opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::ADC ||
                              opcode == arm_fsr_opcode::CMN};

        // (res >> 32) & 1 es 1 o 0.
        auto c{static_cast<u32>(res >> 32)};
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        // Mover lo necesario!
        c = (c & 1) << arm7tdmi::C_SHIFT;
        // movemos lo justo el bit 31 resultante a la posición de V.
        v = (v & (op1 ^ res32) & 0x80000000) >> (31 - arm7tdmi::V_SHIFT);

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
```

He documentado esa función con tal de aumentar la mantenibilidad. Y he añadido algunos comentarios para ver soy consciente de lo que he hecho.

Pero no sé después de ponerme una extensión de documentación mi emacs va lento... Ya veré como solvento esto o igual es cosa del lenguaje o del clangd.

Vale lo he quitado y he optado por hacerlo a mano. Tampoco es que haya muchas opciones si buscamos más funcionalidades.
He pensado que para la memoria y para el tamaño de alcance de proyecto he pensado en utilizar doxygen. Una plataforma que genera documentación del código resultando en una web navegable.

Creo que es algo muy buena práctica.

He cambiado algunos métodos de la lut con tal de hacerlo más al al estilo de stl containers. Como data e invoke.
He refactorizado lut para que no definamos el tipo de retorno porque es algo nicho. Y en su defecto, he utilizado una característica del lenguaje para autodeterminar del tipo de retorno en base a lo que se almacena en la lut si sea llamable habilitará un método que invocación, en otro caso no: dando error de compilación.

Es decir que ahora si almacenamos un int (algo que no es invocable), no dejará realizar el invoke. Si almacenamos funciones sí deja.
Además, ahora sí compila con g++ y clang sin problemas y bajado las versiones porque estoy en debian "versiones estables".
El error es que g++ es más riguroso que clang++, siendo que no permite utilizar using de clases base en derivadas en tiempo de compilación por considerarse incompletas. Pero no ocurre para los tipos concretos. Los using sirven como alias de tipos.

Mis siguientes pasos son:
1. Hacer testing de operand2 y de operaciones de arm fsr. (hoy)
2. Luego si esto va, crear una lut iniciar parcial para saber como direccionar estas operaciones. (hoy-mañana)
3. Probarla. (mañana)
4. Diseñar un esquema básico de memoria con chip. (mañana + 4 días)
5. Preparar estado del arte
6. Preparar preguntas y reunión.

# 21 de julio

con motivo de las celebraciones, el plan no sé cumplió para nada lol.

Por tanto vamos a hacer hoy:

1. Hacer testing de operand2 y de operaciones de arm fsr.
2. Luego si esto va, crear una lut iniciar parcial para saber como direccionar estas operaciones. 
3. Probarla.
4. Diseñar un esquema básico de memoria con chip. (mañana + 4 días) (Vamos a intentarlo, o dejarlo planteado)

Bien, para probar nuestras cosas debemos seguir un orden y por ello cabe recordar las dependencias que tendremos en un futuro.

```

instrucción en crudo y cpu -> [lut de instrucciones] -> [operación fsr] -> [lut de operand2] -> [operand2]

```

La idea de probar es que vamos a probar las dependencias que dependan menos primero. De forma que así aislaremos los fallos por niveles. Siendo que primero, probaremos operand2 y luego fsr. 

Vamos a aprovechar el la estrategia de mocking para probar operand2 directamente desde su llamada de lut. De esta forma mataremos dos pájaros de un tiro, probaremos internamente cómo funciona operand2 y si la lut redirecciona a la que debe. Aunque para un tester más purista lo haría por separado, lo cierto es que aquí podemos considerar la implementación de operand2 y lut de operand2 como completa y es poco susceptible a cambios. Además que su forma principal de interacción es a través de la lut.

Vamos a utilizar una fixture que construya la cpu y el estado del mockeo. El claro beneficio que tiene utilizar una megaplantilla es el rendimiento y que no hay una combinación explosiva de funciones a probar sino que podemos considerarlo todo como un algoritmo y por tanto resulta más fácil ver el transcurso del programa

Vamos a empezar en orden y vamos a ir comprobando las bifurcaciones.

Vale no, vamos a hacer primero pruebas unitarias y luego sobre la lut con mockeos. Aunque en realidad no hace falta para nada. La lut es un array del podemos recuperar el puntero función y ver si lo recuperado coincide. Siendo así que podemos garantizar su correcta ejecución. Podemos establecer un test parametrizado.

Para probar `arm_fsr_operand2_i1_r1` necesitamos solo un caso dado que no tiene bifurcación alguna.
Para probar `arm_fsr_operand2_i1_r0` necesitamos solo un caso dado que no tiene bifurcación alguna pero vamos a comprobar si realmente va bien el carry_out del shift barrel. Por lo que haremos 2.

Ya hemos terminado con i=1, ahora vamos i=0:

Vamos a empezar con los casos especiales y luego seguimos con resto. Los casos especiales siempre tendrán el bit 4 a uno. Y presisaremos de 3 casos más otros 4 para comprobar la activación del carryout, con excepción del lsl.


Vale he encontrado un bug en la cpu y es que no accede bien a los registros `active_registers` por medio del depurador. Vale mala mía, me he olvidado de poner el usr mode mano porque este también cambia los registros. y claro todos los del active son cero porque apuntan al primer elemento. y ningún otro es alterado.

Por otro lado estoy pensando que podríamos seguir matando dos pájaros de un tiro. Y es comprobar que la operación de computar el contenido de operand2 ha ido bien e inmediatamente después ver si en la lut coincide el puntero.
