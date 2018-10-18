



template<typename T, size_type N>                                                                             
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init)                                                           
{                                                                                                             
    desc.extents = derive_extents<N>(init);                                                                   
    compute_strides(desc);                                                                                    
    elems.reserve(desc.size);                                                                                 
    insert_flat(init, elems);                                                                                 
                                                                                                              
    //assert(elems.size() == desc.size);                                                                      
}                                                                                                             
                                                                                                              
                                                                                                              
                                                                                                              
template<typename T, size_type N>                                                                             
template<typename... Exts>                                                                                    
Matrix<T, N>::Matrix(Exts... exts) : desc{exts...}, elems(desc.size)                                          
{}   


template<typename T, size_type N>                                                                             
template<typename T2>                                                                                          
Matrix<T, N>::Matrix(const Matrix_ref<T2, N>& x)                                                               
    : desc{x.descriptor()}, elems(x.cbegin(), x.cend())
{
	desc.start = 0;
//std::cout << "construct\n";
//static_assert(Convertible<U, T>(), "Matrix constructor: Incompatible element types");
}


// and an assignment
template<typename T, size_type N>
template<typename T2>
Matrix<T, N>& Matrix<T, N>::operator=(const Matrix_ref<T2, N>& x)
{
	desc = x.descriptor();
	elems.assign(x.begin(), x.end());
	desc.start = 0;
	//std::cout << "assign\n";
	//static_assert(Convertible<T2, T>(), "Matrix constructor: Incompatible element types");
	return *this;
}                                                                                                           
