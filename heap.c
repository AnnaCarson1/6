#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);

/*
  Хоёр зурвасын чухлыг харьцуулах функц.
  b нь илүү чухал бол 1, бусад үед 0-ыг буцаах функц.
  Өөрөөр хэлбэл a < b үйлдэл юм.
*/
int less(const Msg *a, const Msg *b)
{
        if ( a -> priority < b -> priority ) return 1 ;
        else {
            if ( a -> priority == b -> priority ) {
                if ( a -> time < b -> time ) return 1 ;
                else return 0 ;
            }
            else return 0 ;
        }
}

/*
  Оруулах функц. heap зарчмаар чухлын дарааллыг баримтлан оруулна.
  Ингэхдээ хамгийн чухал зурвас heap-ын оройд хадгалагдана.
  x зурвасыг p-ын зааж буй heap бүтцэд оруулна.
 */
void insert(Heap *p, const Msg x)
{
        p -> h_arr [ p -> h_len ] = x ;
        p -> h_len ++ ;
        swim ( p , p -> h_len - 1 ) ;
}

/*
  Heap бүтцийн swim үйлдэл.
  k нь swim үйлдлийг p-ын зааж буй heap дээр эхлүүлэх индекс.
 */
static void swim(Heap *p, int k)
{
        Msg temp1 , temp2 ;
        while ( k > 0 && less ( & ( p -> h_arr [ k ] ) , & ( p -> h_arr [ ( k - 1 ) / 2 ] ) ) == 1 ) {
            temp1 = p -> h_arr [ k ] ;
            temp2 = p -> h_arr [ ( k - 1 ) / 2 ] ;
            p -> h_arr [ ( k - 1 ) / 2 ] = temp1 ;
            p -> h_arr [ k ] = temp2 ;
            k = ( k - 1 ) / 2 ;
        }
}

/*
  Heap бүтцийн sink үйлдэл.
  k нь sink үйлдлийг p-ын зааж буй heap дээр эхлүүлэх индекс.
 */
static void sink(Heap *p, int k)
{
        Msg temp1 , temp2 ;
        while ( 2 * k + 1 < p -> h_len ) {
            int x = 2 * k + 1 ;
            if ( x + 1 < p -> h_len && less ( & ( p -> h_arr [ x + 1 ] ) , & ( p -> h_arr [ x ] ) ) == 1 ) {
                x ++ ;
            }
            if ( less ( & ( p -> h_arr [ k ] ) , & ( p -> h_arr [ x ] ) ) == 1 ) {
                break ;
            }
            temp1 = p -> h_arr [ k ] ;
            temp2 = p -> h_arr [ x ] ;
            p -> h_arr [ k ] = temp2 ;
            p -> h_arr [ x ] = temp1 ;
            k = x ;
        }
}

/*
  p-ын зааж буй heap бүтцээс оройн элементийг гаргаад буцаах функц.
  Гаргасны дараа орой бүрийн хувьд heap зарчим хадгалах ёстой.
 */
Msg delMin(Heap *p)
{
        Msg temp ;
        strcpy ( temp . text , "" ) ;
        if ( p -> h_len == 0 ) return temp ;
        temp = p -> h_arr [ 0 ] ;
        p -> h_arr [ 0 ] = p -> h_arr [ p -> h_len - 1 ] ;
        p -> h_len -- ;
        sink ( p , 0 ) ;
        return temp ;
}

