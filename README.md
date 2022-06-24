# ESE_CRT v1.0.1 

ESE_CRT es una aplicación para Windpws para simular el movimiento del ESE_CRT de 3 ejes y 
generar superficies complejas utilizando planos y mallas a partir 
de puntos, líneas y curvas con un acabado final en el editor 3D Autodesk 
Inventor. 



## [Descargar ESE_CRT](https://github.com/Esteban1914/ESE_CART/raw/master/media/ESE_CRT/ESE_CRT.rar)

![Foto de ESE_CRT](https://github.com/Esteban1914/ESE_CRT/blob/master/media/ESE_CRT.png)
![Foto de ESE_CRT](https://github.com/Esteban1914/ESE_CRT/blob/master/media/ESE_CRT1.png)

##Simulador: [ESE_CRT_Simulator](https://github.com/Esteban1914/ESE_CRT_Simulator)

##Codigo de arduino: [ESE_CRT_Arduino](https://github.com/Esteban1914/ESE_CRT_Arduino)

## Plataforma
>Windows

## Lenguaje
>C++ 

## Librerias utilizadas
> - OpenGL(Simular el brazo en un entorno 3D)
> - winsock(Conexiones por Sockets)
> - libxl(Comunicación de la Aplicacion con Autodesk Inventor)

## Conexiones
> - Puerto Serie

## Sobre los desarrolladores
>***Creación y mantenimiento del brazo físico:***
> - Telegram:  @ACB273
>
>***Comunicación arduino PC y desarrollo de la aplicación:***
> - Telegram:  @EstebanACB2
> - Correo:    acevedoesteban999@gmail.com

***Importante para el desarrollo en Visual Studio 2012***
> 1. Configuration Properites->General->characterSet=Not Set
> 2. Configuration Properites->General->Common Language Runtime Support=No Common Language Runtime Support
> 3. C/C++->General->Additional Include Directories=../libxl/include_cpp && ../freeglut/include
> 4. Linker->General->Additional Library Directories=../freegut/lib/ && ../xlms/lib/)
> 5. Linker->Input->Additinal Dependencies=freeglut.lib && libxl.lib