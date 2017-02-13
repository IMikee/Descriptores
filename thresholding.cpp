
//Compilar:
// g++ -O2 thresholding.cpp -o test `pkg-config --cflags opencv` `pkg-config --libs opencv`

//ejercutar:
// ./test rutaDeLaImagen

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//variables Globales
uchar threshold = 160;

//Declaracion de Funciones
cv::Mat binarizeAt(cv::Mat image); //recorre la imagen con at
cv::Mat binarizeP(cv::Mat image); //recorre la imagen con apuntadores

/*******************************************************************
Si se recorrera toda la imagen es más efectivo usar apuntadores,
Si requiero ciertos pixeles es mas efectivo ******at*****
********************************************************************/

int main(int argc, char const *argv[])
{

  //Version OpenCV
  std::cout << "VERSION : " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << std::endl;

  //Espera ruta para leer la imagen
  if(argc != 2)
  {
      std::cerr << "./ejecutal imagen.ext" << std::endl;
      return -1;
  }

  //Lee la imagen
  cv::Mat image = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
  {
    std::cerr << "No se puede cargar la imagen" << std::endl;
  }


  //muestra la imagen
  cv::namedWindow("Imagen de Entrada",CV_WINDOW_AUTOSIZE);
  cv::imshow("Imagen de Entrada",image);

  //image = binarizeAt(image);
  image = binarizeP(image);

  //muestra la imagen binarizada
  cv::namedWindow("Imagen de Salida", CV_WINDOW_AUTOSIZE);
  cv::imshow("Imagen de Salida",image);

  //Mantiene las imagenes hasta presionar una tecla
  cv::waitKey(0);

  return 0;
}

//recorre la imagen con at
cv::Mat binarizeAt(cv::Mat image)
{
  //recorre imagen
  for (int i = 0; i < image.rows; i++)
    for (int j = 0; j < image.cols; j++)
      image.at<uchar>(i,j) = image.at<uchar>(i,j) < threshold ? 0:255; //umbralizacion

  return image;
}

//Recorre la imagen con apuntadores
cv::Mat binarizeP(cv::Mat image)
{
  //recorre la imagen
  for (int i = 0; i < image.rows; i++)
  {
    uchar* ptrRow = image.ptr(i); //aputandor a la fila
    for (int j = 0; j < image.cols; j++)
      ptrRow[j] = ptrRow[j] < threshold ? 0:255; //umbralizacion
  }

  return image;
}
