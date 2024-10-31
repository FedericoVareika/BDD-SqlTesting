#ifndef X 
#define X(a, ...) tabla_##a,
#endif

#ifndef Y 
#define Y(...) 
#endif

#ifndef Z 
#define Z(...) 
#endif

#ifndef EMPTY
#define EMPTY {}
#endif 

#define DepAsignaRol() {Y(Asistente), Y(Rol)}
#define DepCompra() {Y(Configuracion), Y(Usuario), Y(Count)}

X(Asistente, EMPTY, EMPTY)                                                   
X(Rol, EMPTY, EMPTY)                                                        
X(AsignaRol, DepAsignaRol(), {Z(Asistente), Z(Rol)})                 
X(Configuracion, EMPTY, {Z(Asistente)})                                      
X(Usuario, EMPTY, {Z(Asistente)})                                            
X(Compra, DepCompra(), {Z(Configuracio), Z(Usuario)})

#undef X
#undef Y
#undef Z
#undef EMPTY
