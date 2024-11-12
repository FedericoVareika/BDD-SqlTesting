#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ArrayLen(arr) (sizeof((arr)) / sizeof((*arr)))
#define MAX_DATE 365

typedef enum { false, true } bool;

int random_int(int max, int min) {
  int dif = max - min;
  return rand() % dif + min;
}

int random_idx(int len) { return rand() % len; }

unsigned int shuffle_idx(int idx) {
  int ret = (((idx ^ 0xf7f7f7f7) * 0x8364abf7) ^ 0xf00bf00b) * 0xf81bc437;
  return ret;
}

char *nombres[] = {
    "Juan",
    "José Luis",
    "José",
    "María Guadalupe",
    "Francisco",
    "Guadalupe",
    "María",
    "Juana",
    "Antonio",
    "Jesús",
    "Miguel Ángel",
    "Pedro",
    "Alejandro",
    "Manuel",
    "Margarita",
    "María Del Carmen",
    "Juan Carlos",
    "Roberto",
    "Fernando",
    "Daniel",
    "Carlos",
    "Jorge",
    "Ricardo",
    "Miguel",
    "Eduardo",
    "Javier",
    "Rafael",
    "Martín",
    "Raúl",
    "David",
    "Josefina",
    "José Antonio",
    "Arturo",
    "Marco Antonio",
    "José Manuel",
    "Francisco Javier",
    "Enrique",
    "Verónica",
    "Gerardo",
    "María Elena",
    "Leticia",
    "Rosa",
    "Mario",
    "Francisca",
    "Alfredo",
    "Teresa",
    "Alicia",
    "María Fernanda",
    "Sergio",
    "Alberto",
    "Luis",
    "Armando",
    "Alejandra",
    "Martha",
    "Santiago",
    "Yolanda",
    "Patricia",
    "María De Los Ángeles",
    "Juan Manuel",
    "Rosa María",
    "Elizabeth",
    "Gloria",
    "Ángel",
    "Gabriela",
    "Salvador",
    "Víctor Manuel",
    "Silvia",
    "María De Guadalupe",
    "María De Jesús",
    "Gabriel",
    "Andrés",
    "Óscar",
    "Guillermo",
    "Ana María",
    "Ramón",
    "María Isabel",
    "Pablo",
    "Ruben",
    "Antonia",
    "María Luisa",
    "Luis Ángel",
    "María Del Rosario",
    "Felipe",
    "Jorge Jesús",
    "Jaime",
    "José Guadalupe",
    "Julio Cesar",
    "José De Jesús",
    "Diego",
    "Araceli",
    "Andrea",
    "Isabel",
    "María Teresa",
    "Irma",
    "Carmen",
    "Lucía",
    "Adriana",
    "Agustín",
    "María De La Luz",
    "Gustavo",
};

char *genero[] = {
    "Femenino",
    "Masculino",
    "No binario",
};

char *tipo[] = {
    "Tutor",
    "Amigo",
    "Coach",
};

char *ropa[] = {
    "Verano", "Primavera", "Anime", "Oficina", "Fiesta", "Deporte", "Camisetas",
};

char *interes[] = {
    "Juegos",
    "Deportes",
    "Historia",
    "Moda",
};

char *rasgo[] = {
    "Seguro",  "Tímido",    "Energético", "Práctico",
    "Soñador", "Artístico", "Lógico",
};

char *voz[] = {
    "Femenina",
    "Masculina",
};

char vigente[] = {
    'S',
    'N',
};

char *rango_edad[] = {
    "18-24", "25-34", "35-44", "45-54", "55-64", "65 o más",
};

typedef struct {
  int idAsistente;
  char *nombre;
  char *genero;
} Asistente;

typedef struct {
  int idRol;
  char *tipo;
} Rol;

typedef struct {
  int idAsignaRol;
  int idAsistente;
  int idRol;
} AsignaRol;

typedef struct {
  int idConfiguracion;
  char *ropa;
  char *interes;
  char *rasgo;
  char *voz;
  int costoGemas;
  int costoMonenas;
  int idAsistente;
  char vigente;
} Configuracion;

typedef struct {
  int idUsuario;
  char *email;
  char *nombre;
  char *rangoEdad;
  int fechaRegistro;
  int saldoGemas;
  int saldoMonedas;
  int idAsistente;
} Usuario;

typedef struct {
  int idCompra;
  int idConfiguracion;
  int idUsuario;
  char *email;
  int fechaCompra;
  int totalGemas;
  int totalMonedas;
} Compra;

#define cantidad(a) cant##a
#define gen_random(a) random##a
#define tabla(a) tabla##a
#define enum_tabla(a) tabla_##a,

typedef enum {
  tabla_Null,
#define X(a, ...) tabla_##a,
#include "tablas.inl"
  tabla_Count,
#undef X
} TablasEnum;

// Random create function declarations
#define X(a, ...) a gen_random(a)(int idx);
#include "tablas.inl"
#undef X

// Nombres de tablas lookup
char *nombres_lookup[] = {
#define X(a, ...) [tabla_##a] = #a,
#include "tablas.inl"
#undef X
};

// Nombres de valores para insert lookup
char *nombres_atributos_lookup[tabla_Count] = {
    [tabla_Asistente] = "(idAsistente, nombre, genero)",
    [tabla_Rol] = "(idRol, tipo)",
    [tabla_AsignaRol] = "(idAsistente, idRol)",
    [tabla_Configuracion] = "(idConfiguracion, ropa, interes, rasgo, voz, "
                            "costoGemas, costoMonenas, idAsistente, vigente)",
    [tabla_Usuario] = "(email, nombre, rangoEdad, fechaRegistro, saldoGemas, "
                      "saldoMonedas, idAsistente)",
    [tabla_Compra] =
        "(idConfiguracion, email, fechaCompra, totalGemas, totalMonedas)",
};

// Cantidades lookup
int cantidades[tabla_Count] = {};

// Tablas union
typedef union {
#define X(a, ...) a *tabla##a;
#include "tablas.inl"
#undef X
} TablasPtrUnion;

// Arrays lookup
TablasPtrUnion arrays[tabla_Count] = {};

#define X(a, ...) a *tabla(a);
#include "tablas.inl"
#undef X

#define X(a, ...)                                                              \
  int get_id##a(int idx) { return arrays[tabla_##a].tabla##a[idx].id##a; }
#include "tablas.inl"
#undef X

// Dependencias primarias
TablasEnum deps[][tabla_Count] = {
    [tabla_Null] = {},
#define Y(a) tabla_##a
#define EMPTY                                                                  \
  {}
#define X(a, deps, ...) [tabla_##a] = deps,
#include "tablas.inl"
#undef X
#undef EMPTY
};

void clampCants() {
  for (int i = 1; i < tabla_Count; i++) {
    bool tieneDeps = false;
    TablasEnum *dep = deps[i];
    int max_cant = 1;
    for (int j = 1; j < tabla_Count; j++) {
      if (dep[j] == tabla_Null)
        continue;
      if (dep[j] == tabla_Count) {
        max_cant *= 10;
        continue;
      }

      tieneDeps = true;
      max_cant *= cantidades[j];
    }

    if (tieneDeps && max_cant < cantidades[i])
      cantidades[i] = max_cant;
  }
}

Asistente randomAsistente(int idx) {
  Asistente ret = {
      .idAsistente = idx,
      .nombre = nombres[random_idx(ArrayLen(nombres))],
      .genero = genero[random_idx(ArrayLen(genero))],
  };
  return ret;
}

Rol randomRol(int idx) {
  Rol ret = {
      .idRol = idx,
      .tipo = tipo[random_idx(ArrayLen(tipo))],
  };
  return ret;
}

AsignaRol randomAsignaRol(int idx) {
  AsignaRol ret = {
      .idAsignaRol = idx,
  };

  ret.idRol = shuffle_idx(idx) % cantidades[tabla_Rol];
  ret.idAsistente = shuffle_idx(idx) % cantidades[tabla_Asistente];
  return ret;
}

Configuracion randomConfiguracion(int idx) {
  Configuracion ret = {
      .idConfiguracion = idx,
      .idAsistente = idx % cantidades[tabla_Asistente],
      .ropa = ropa[random_idx(ArrayLen(ropa))],
      .interes = interes[random_idx(ArrayLen(interes))],
      .voz = voz[random_idx(ArrayLen(voz))],
      .rasgo = rasgo[random_idx(ArrayLen(rasgo))],
      .costoGemas = random_int(1, 0) * random_int(100, 1),
      .costoMonenas = random_int(1, 0) * random_int(100, 1),
      .vigente = vigente[random_idx(ArrayLen(vigente))],
  };
  return ret;
}

#include <string.h>

Usuario randomUsuario(int idx) {
  char *nombre = nombres[random_idx(ArrayLen(nombres))];
  Usuario ret = {
      .idUsuario = idx,
      .idAsistente = idx % cantidades[tabla_Asistente],
      .nombre = nombre,
      .rangoEdad = rango_edad[random_idx(ArrayLen(rango_edad))],
      // se define en el output
      .email = NULL,
      .saldoGemas = random_int(1000, 0),
      .saldoMonedas = random_int(1000, 0),
  };

  ret.fechaRegistro = shuffle_idx(idx) % MAX_DATE;
  return ret;
}

Compra randomCompra(int idx) {
  Compra ret = {
      .idCompra = idx,
      // se define en el output segun el idUsuario
      /* .idUsuario = random_idx(cantidades[tabla_Usuario]), */
      .email = NULL,
      .totalMonedas = random_int(1000, 1),
      .totalGemas = random_int(1000, 1),
  };

  ret.idConfiguracion = shuffle_idx(idx) % cantidades[tabla_Configuracion];
  ret.idUsuario = shuffle_idx(idx) % cantidades[tabla_Usuario];

  /* idx /= cantidades[tabla_Configuracion]; */
  // usar dateadd de sql para hacer q fechacompra sea un int
  ret.fechaCompra = shuffle_idx(idx) % (MAX_DATE - 1) + 1;
  /* idx /= MAX_DATE; */
  /* ret.idUsuario = idx % cantidades[tabla_Usuario]; */
  return ret;
}

void print_Asistente(FILE *out, Asistente asistente) {
  fprintf(out, "(%d, '%s', '%s')", asistente.idAsistente, asistente.nombre,
          asistente.genero);
}

void print_Rol(FILE *out, Rol rol) {
  fprintf(out, "(%d, '%s')", rol.idRol, rol.tipo);
}

void print_AsignaRol(FILE *out, AsignaRol asignarol) {
  fprintf(out, "(%d, %d)", asignarol.idAsistente, asignarol.idRol);
}

void print_Configuracion(FILE *out, Configuracion configuracion) {
  fprintf(out, "(%d, '%s', '%s', '%s', '%s', %d, %d, %d, '%c')",
          configuracion.idConfiguracion, configuracion.ropa,
          configuracion.interes, configuracion.rasgo, configuracion.voz,
          configuracion.costoGemas, configuracion.costoMonenas,
          configuracion.idAsistente, configuracion.vigente);
}

void print_Usuario(FILE *out, Usuario usuario) {
  int dia = usuario.fechaRegistro % 28 + 1;
  int mes = (usuario.fechaRegistro / 30) % 12 + 1;
  fprintf(out,
          "('%d%s@gmail.com', '%s', '%s', Date '2024-%d-%d', "
          "%d, %d, %d)",
          usuario.idUsuario, usuario.nombre, usuario.nombre, usuario.rangoEdad,
          mes, dia, usuario.saldoGemas, usuario.saldoMonedas,
          usuario.idAsistente);
}
void print_Compra(FILE *out, Compra compra) {
  int dia = compra.fechaCompra % 28 + 1;
  int mes = (compra.fechaCompra / 30) % 12 + 1;
  fprintf(out, "(%d, '%d%s@gmail.com', Date '2024-%d-%d', %d, %d)",
          compra.idConfiguracion, compra.idUsuario,
          arrays[tabla_Usuario].tablaUsuario[compra.idUsuario].nombre, mes, dia,
          compra.totalGemas, compra.totalMonedas);
}

/* fprintf(out, "INSERT INTO " #a " %s \nVALUES",                         \ */
/*         nombres_atributos_lookup[tabla_##a]);                          \ */
void imprimirSQL(FILE *out) {
#define X(a, ...)                                                              \
  fprintf(out, "INSERT ALL\n");                                                \
  for (int i = 0; i < cantidades[tabla_##a]; i++) {                            \
    fprintf(out, "INTO " #a " %s VALUES ",                                     \
            nombres_atributos_lookup[tabla_##a]);                              \
    a value = arrays[tabla_##a].tabla##a[i];                                   \
    print_##a(out, value);                                                     \
    fprintf(out, "\n");                                                        \
  }                                                                            \
  fprintf(out, "SELECT 1 FROM DUAL;\n");
#include "tablas.inl"
#undef X
  /* fprintf(out, ";\n"); \ */
}

#define usage                                                                  \
  "%s [seed] [filename.sql] \n"                                                \
  "   [seed] [filename.sql] [max elementos]\n"                                 \
  "   [seed] [filename.sql] [min elementos] [max elementos]\n"

int main(int argc, char **argv) {
  if (argc < 3) {
    printf(usage, argv[0]);
    return 1;
  }

  int seed = atoi(argv[1]);
  srand(seed);

  FILE *file = fopen(argv[2], "w");
  assert(file);

  int max_elementos = 1;
  int min_elementos = 1;
  if (argc == 4) {
    max_elementos = atoi(argv[3]);
  } else {
    max_elementos = atoi(argv[4]);
    min_elementos = atoi(argv[3]);
  }

  // Init cantidades
#define X(a, ...)                                                              \
  cantidades[tabla_##a] = random_int(max_elementos, min_elementos);
#include "tablas.inl"
#undef X

  // Asegurar que hay suficientes elementos que pertenezcan a una FK y PK
  //
  // Por ejemplo no pueden haber 100 AsignaRol pero 5 Roles y 5 Asistentes
  // Si esto pasa, hay que clampear el valor de cantAsignaRol

  clampCants();

  // Init tablas
#define X(a, ...)                                                              \
  arrays[tabla_##a].tabla##a = malloc(sizeof(a) * cantidades[tabla_##a]);
#include "tablas.inl"
#undef X

  // Randomizar todos
#define X(a, ...)                                                              \
  for (int i = 0; i < cantidades[tabla_##a]; i++) {                            \
    arrays[tabla_##a].tabla##a[i] = gen_random(a)(i);                          \
  }
#include "tablas.inl"
#undef X

  imprimirSQL(file);

  return 0;
}
