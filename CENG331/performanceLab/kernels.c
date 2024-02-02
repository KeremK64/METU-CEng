/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
    "DUMEN", /* Team Name */

    "e264441",      /* First student ID */
    "Kerem Karabacak", /* First student name */

    "e257598", /* Second student ID */
    "Aytaç Sekmen"  /* Second student name */

};

/*******************************************************
 * BATCHED MATRIX MULTIPLICATION \W SUM REDUCTION KERNEL
 *******************************************************/

/*********************************************************************************
 * Your different versions of the batched matrix multiplication functions go here
 *********************************************************************************/

/*
 * naive_batched_mm - The naive baseline version of batched matrix multiplication
 */
char naive_batched_mm_descr[] = "naive_batched_mm: Naive baseline implementation";
void naive_batched_mm(int dim, int *b_mat, int *mat, int *dst)
{
    int i, j, k, l;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            for (k = 0; k < dim; k++)
            {
                if (i == 0)
                {
                    dst[RIDX(j, k, dim)] = 0;
                }
                for (l = 0; l < dim; l++)
                {
                    dst[RIDX(j, k, dim)] += b_mat[RIDX(i * dim + j, l, dim)] * mat[RIDX(l, k, dim)];
                }
            }
        }
    }
}


/*
 * batched_mm - Your current working version of batched matrix multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char batched_mm_descr[] = "DUMEN BATCHED MM";
void batched_mm(int dim, int *b_mat, int *mat, int *dst)
{
    int j, k, l;
    int dimSquare = dim * dim;
    int deger=dimSquare*(dim);
    int dim_intsize = dimSquare * sizeof(int);
    int *transpose1 = malloc(dim_intsize);
    int *transpose1_cursor = transpose1;
    int resultara1   = 0;
    int resultara2   = 0;
    int resultara3   = 0;
    int resultara4   = 0;
    int resultara5   = 0;
    int resultara6   = 0;
    int resultara7   = 0;
    int resultara8   = 0;
    int resultara9   = 0;
    int resultara10  = 0;
    int resultara11  = 0;
    int resultara12  = 0;
    int resultara13  = 0;
    int resultara14  = 0;
    int resultara15  = 0;
    int resultara16  = 0;
    int resultara17  = 0;
    int resultara18  = 0;
    int resultara19  = 0;
    int resultara20  = 0;
    int resultara21  = 0;
    int resultara22  = 0;
    int resultara23  = 0;
    int resultara24  = 0;
    int resultara25  = 0;
    int resultara26  = 0;
    int resultara27  = 0;
    int resultara28  = 0;
    int resultara29  = 0;
    int resultara30  = 0;
    int resultara31  = 0;
    int resultara32  = 0;

    int *ptrtoplam=b_mat;
    int *newMatrix = malloc(dim_intsize);
    int *newMatrix_cursor = newMatrix;
    int *first_mat=mat;
    for (int i = 0; i < dim; i++)
    {
        transpose1 = transpose1_cursor + i;
        for (int j = 0; j < dim; j += 32)
        {
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            ((*transpose1)) = *first_mat++;
            transpose1 += dim;
            for (int k = 0; k < dim; k++)
            {
                
                resultara1 += *ptrtoplam++;
                resultara2 += *ptrtoplam++;
                resultara3 += *ptrtoplam++;
                resultara4 += *ptrtoplam++;
                resultara5 += *ptrtoplam++;
                resultara6 += *ptrtoplam++;
                resultara7 += *ptrtoplam++;
                resultara8 += *ptrtoplam++;
                resultara9 += *ptrtoplam++;
                resultara10 += *ptrtoplam++;
                resultara11 += *ptrtoplam++;
                resultara12 += *ptrtoplam++;
                resultara13 += *ptrtoplam++;
                resultara14 += *ptrtoplam++;
                resultara15 += *ptrtoplam++;
                resultara16 += *ptrtoplam++;
                resultara17 += *ptrtoplam++;
                resultara18 += *ptrtoplam++;
                resultara19 += *ptrtoplam++;
                resultara20 += *ptrtoplam++;
                resultara21 += *ptrtoplam++;
                resultara22 += *ptrtoplam++;
                resultara23 += *ptrtoplam++;
                resultara24 += *ptrtoplam++;
                resultara25 += *ptrtoplam++;
                resultara26 += *ptrtoplam++;
                resultara27 += *ptrtoplam++;
                resultara28 += *ptrtoplam++;
                resultara29 += *ptrtoplam++;
                resultara30 += *ptrtoplam++;
                resultara31 += *ptrtoplam++;
                resultara32 += *ptrtoplam++;
                ptrtoplam += dimSquare-32;
            }
            ptrtoplam-=(deger-32);
            *newMatrix++ = resultara1   ;
            *newMatrix++ = resultara2   ;
            *newMatrix++ = resultara3   ;
            *newMatrix++ = resultara4   ;
            *newMatrix++ = resultara5   ;
            *newMatrix++ = resultara6   ;
            *newMatrix++ = resultara7   ;
            *newMatrix++ = resultara8   ;
            *newMatrix++ = resultara9   ;
            *newMatrix++ = resultara10  ;
            *newMatrix++ = resultara11  ;
            *newMatrix++ = resultara12  ;
            *newMatrix++ = resultara13  ;
            *newMatrix++ = resultara14  ;
            *newMatrix++ = resultara15  ;
            *newMatrix++ = resultara16  ;
            *newMatrix++ = resultara17  ;
            *newMatrix++ = resultara18  ;
            *newMatrix++ = resultara19  ;
            *newMatrix++ = resultara20  ;
            *newMatrix++ = resultara21  ;
            *newMatrix++ = resultara22  ;
            *newMatrix++ = resultara23  ;
            *newMatrix++ = resultara24  ;
            *newMatrix++ = resultara25  ;
            *newMatrix++ = resultara26  ;
            *newMatrix++ = resultara27  ;
            *newMatrix++ = resultara28  ;
            *newMatrix++ = resultara29  ;
            *newMatrix++ = resultara30  ;
            *newMatrix++ = resultara31  ;
            *newMatrix++ = resultara32  ;

            resultara1   = 0;
            resultara2   = 0;
            resultara3   = 0;
            resultara4   = 0;
            resultara5   = 0;
            resultara6   = 0;
            resultara7   = 0;
            resultara8   = 0;
            resultara9   = 0;
            resultara10  = 0;
            resultara11  = 0;
            resultara12  = 0;
            resultara13  = 0;
            resultara14  = 0;
            resultara15  = 0;
            resultara16  = 0;
            resultara17  = 0;
            resultara18  = 0;
            resultara19  = 0;
            resultara20  = 0;
            resultara21  = 0;
            resultara22  = 0;
            resultara23  = 0;
            resultara24  = 0;
            resultara25  = 0;
            resultara26  = 0;
            resultara27  = 0;
            resultara28  = 0;
            resultara29  = 0;
            resultara30  = 0;
            resultara31  = 0;
            resultara32  = 0;
        }
    }
    int *ptr2;
    int result = 0;
    int j_dim = 0;
    for (j = 0; j < dim; j++)
    {
        transpose1=transpose1_cursor;
        int *temp_ptr2 = &newMatrix_cursor[j_dim];

        for (k = 0; k < dim; k++)
        {
            ptr2 = temp_ptr2;
            for (l = 0; l < dim; l += 32)
            {
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
                result += (*ptr2++) * (*transpose1++);
            }
            *dst = result;
            dst++;
            result = 0;
        }
        j_dim+=dim;
    }

    free(transpose1_cursor);
    free(newMatrix_cursor);
}
/*********************************************************************
 * register_batched_mm_functions - Register all of your different versions
 *     of the batched matrix multiplication functions  with the driver by calling the
 *     add_batched_mm_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_batched_mm_functions()
{
    //add_batched_mm_function(&naive_batched_mm, naive_batched_mm_descr);
    add_batched_mm_function(&batched_mm, batched_mm_descr);
    /* ... Register additional test functions here */
}

/************************
 * POINT REFLECTION KERNEL
 ************************/

/*********************************************************
 * Your different versions of the point reflection go here
 *********************************************************/

/*
 * naive_reflect - The naive baseline version of point reflection
 */
char naive_reflect_descr[] = "Naive Point Reflection: Naive baseline implementation";
void naive_reflect(int dim, int *src, int *dst)
{
    int i, j;

    // RIDX(i,j,n) ((i)*(n)+(j))

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            dst[RIDX(dim - 1 - i, dim - 1 - j, dim)] = src[RIDX(i, j, dim)];
        }
    }
}

/*
 * reflect - Your current working version of reflect
 * IMPORTANT: This is the version you will be graded on
 */
char reflect_descr[] = "DUMEN REFLECTION";
void reflect(int dim, int *src, int *dst){
    int i, j;
    int* ptr = &dst[dim * dim - 1];

    for (i = 0; i < dim; i+=8) {
        
	    for (j = 0; j < dim; j += 8) {
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);
            *(ptr--) = *(src++);

            
            
            
        }
    }
}

/******************************************************************************
 * register_reflect_functions - Register all of your different versions
 *     of the reflect with the driver by calling the
 *     add_reflect_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ******************************************************************************/

void register_reflect_functions()
{
    //add_reflect_function(&naive_reflect, naive_reflect_descr);
    add_reflect_function(&reflect, reflect_descr);
    /* ... Register additional test functions here */
}
