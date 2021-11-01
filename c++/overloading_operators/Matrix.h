#pragma once
#include <unordered_map>
#include <array>
#include <tuple>

namespace utils 
{

    /**
     * @brief Генерация типа гомогенного кортежа, содержащего N элементов типа T.
     * @tparam N - размер кортежа.
     * @tparam T - тип элементов.
     */
    template <size_t N, typename T>
    struct gen_tuple_t {
        using type = decltype(std::tuple_cat(std::declval<std::tuple<T>>(),
            std::declval<typename gen_tuple_t<N - 1, T>::type>()));
    };

    /**
     * @brief Генерация типа гомогенного кортежа, содержащего N элементов типа T (конец рекурсии).
     * @tparam T - тип элементов.
     */
    template<typename T>
    struct gen_tuple_t<1, T> {
        using type = std::tuple<T>;
    };

    /**
     * @brief Генерация типа кортежа при добавлении элемента в конец кортежа.
     * @tparam T - тип кортежа.
     * @tparam U - тип добавляемого элемента.
     */
    template<typename T, typename U>
    struct append_tuple_t {
        using type = decltype(std::tuple_cat(std::declval<T>(), 
            std::declval<std::tuple<U>>()));
    };

    /**
     * @brief Дать подкортеж данного кортежа.
     * @tparam T - тип кортежа.
     * @tparam Indices - индексы элементов кортежа, которые необходимо поместить в подкортеж.
     */
    template <typename T, size_t... Indices>
    auto get_subtuple(const T& tuple, std::index_sequence<Indices...>) {
        auto subtuple = std::make_tuple(std::get<Indices>(tuple)...);
        return subtuple;
    } 

    template<typename T>
    struct hash
    {
        static constexpr size_t len = std::tuple_size<T>::value;
        /**
         * @brief Конвертор кортежа в std::array.
         * @tparam Indices - индексы элементов кортежа, которые необходимо поместить в массив.
         * @param tuple - кортеж.
         */
        template <size_t... Indices>
        auto t2a(const T& tuple, std::index_sequence<Indices...>) const {
            std::array<size_t, len> arr{{std::get<Indices>(tuple)...}};
            return arr;
        }

        /**
         * @brief Собственно само вычисление хэша (заимствовано из boost hash_combine).
         * @param tuple - кортеж.
         */
        size_t operator() (const T& tuple) const {
            size_t seed = 0;
            // boost hash_combine.
            for(auto it: t2a(tuple, std::make_index_sequence<len>{}))
            seed ^= std::hash<size_t>()(it) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };      
} // namespace utils

// Matrix
// https://github.com/PetrLiutik-selfstudy/otus_cpp_matrix
// https://docs.google.com/spreadsheets/d/1qEftVZcKDWbhLtYKa-28_75W4NfL3myYmwYjo2G3V1Q/edit#gid=389622953


/**
 * @brief Шаблон N-мерной матрицы.
 * @tparam T - тип элемента матрицы.
 * @tparam empty_val - значение пустого элемента матрицы.
 * @tparam N - размерность матрицы (по умолчанию 2).
 */
template<typename T, T empty_val, size_t N = 2>
class Matrix
{
    static_assert(N > 0, "Incorrect number of dimensions. Must be greater than 0.");

    using index_t = typename utils::gen_tuple_t<N, size_t>::type;
    using storage_t = std::unordered_map<index_t, T, utils::hash<index_t>>;

    /**
    * @brief Шаблон прокси для имитации N-мерной матрицы.
    * @tparam F - тип кортежа, содержащего индексы для обращения к элементу матрицы.
    * @tparam ind - номер индекса по порядку.
    */
    template <typename F, size_t ind>
    class matrix_proxy {
        public:
            matrix_proxy(storage_t& storage, const F& index) : 
                storage_{storage}
                , index_(index)
            {}

            /**
             * @brief Оператор [].
             * @param elem_ind - индекс элемента по текущему "измерению" матрицы.
             * @return следующий прокси.
             */
            auto operator [] (size_t elem_ind) 
            {
                auto nextIndex = std::tuple_cat(index_, std::make_tuple(elem_ind));
                return matrix_proxy<decltype(nextIndex), ind - 1> {storage_, nextIndex};
            }

        private:
            storage_t& storage_;
            F index_;
    };

    /**
     * @brief Шаблон прокси для имитации N-мерной матрицы (конец рекурсии).
     * @tparam F - тип кортежа, содержащего индексы для обращения к элементу матрицы.
     */
    template<typename F>
    class matrix_proxy<F, 0> {
    public:
        matrix_proxy(storage_t& storage, F& index) :
            storage_{ storage }
            , index_{ index }
        {}

        auto& operator = (const T& value)
        {
            if (value == empty_val)
            {
                storage_.erase(index_);
                return empty_val_;
            }
            return storage_[index_] = value;
        }

        operator const T& () const
        {
            auto it = storage_.find(index_);
            return it == storage_.cend() ? empty_val_ : it->second;
        }
    private:
        storage_t& storage_;
        F index_;
        T empty_val_{ empty_val };
    };

public:
    using index_val_t = typename utils::append_tuple_t<index_t, T>::type;

    Matrix() = default;
    Matrix(const index_val_t& index_val)
    {
        auto index = utils::get_subtuple(index_val, std::make_index_suquence<N>{});
        auto value = std::get<N>(index_val);
        if (value != empty_val) 
        {
            storage_[index] = value;
        }
    }

        /**
     * @brief Конструктор со списком инициализации из кортежей с индексами и значениями.
     * @param list - список инициализации.
     */
    Matrix(const std::initializer_list<index_val_t>& list) {
      for(const auto& it: list) {
        auto index = utils::get_subtuple(it, std::make_index_sequence<N>{});
        auto value = std::get<N>(it);
        if(value != empty_val) {
          storage_[index] = value;
        }
      }
    }

    Matrix(const Matrix& mat) = default;
    Matrix(Matrix&& mat) noexcept {
        mat.swap(*this);
    }

    Matrix& operator = (const Matrix& mat)
    {
        Matrix<T, empty_val, N> tmp(mat);
        tmp.swap(*this);
        return *this;
    }

    Matrix& operator = (Matrix&& mat) noexcept
    {
        mat.swap(*this);
        return *this;
    }

    ~Matrix() = default;

    //-----------------------------

    void swap(Matrix& other) 
    {
        std::swap(storage_, other.storage_);
    }

    auto operator [] (size_t elem_ind) 
    {
        auto index = std::make_tuple(elem_ind);
        return matrix_proxy<decltype (index), N - 1>{storage_, index};
    }

    auto operator []  (size_t elem_ind) const
    {
        auto index = std::make_tuple(elem_ind);
        return matrix_proxy<decltype (index), N - 1>{storage_, index};
    }

    size_t size()
    {
        return sotrage_.size();
    }

    /**
 * @brief Класс итератора матрицы.
 */
    struct iterator : std::iterator<std::bidirectional_iterator_tag, storage_iterator_t> {
        explicit iterator(storage_iterator_t it) : current_{ it } {}

        iterator& operator ++() {
            current_++;
            return *this;
        }

        iterator operator ++(int) {
            iterator temp = *this;
            current_++;
            return temp;
        }

        iterator& operator --() {
            current_--;
            return *this;
        }

        iterator operator --(int) {
            iterator temp = *this;
            current_--;
            return temp;
        }

        auto operator *() {
            return std::tuple_cat((*current_).first, std::make_tuple((*current_).second));
        }

        bool operator == (const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator != (const iterator& other) const {
            return !(*this == other);
        }

    private:
        storage_iterator_t current_{};
    };

    /**
     * @brief Дать итератор на начало матрицы.
     * @return итератор на начало матрицы.
     */
    iterator begin() {
        return iterator(storage_.begin());
    }

    /**
     * @brief Дать итератор на конец матрицы.
     * @return итератор на конец матрицы.
     */
    iterator end() {
        return iterator(storage_.end());
    }

    /**
     * @brief Дать реверсный итератор на начало матрицы.
     * @return реверсный итератор на начало матрицы.
     */
    iterator rbegin() {
        return iterator(storage_.rbegin());
    }

    /**
     * @brief Дать реверсный итератор на конец матрицы.
     * @return реверсный итератор на конец матрицы.
     */
    iterator rend() {
        return iterator(storage_.rend());
    }
    
private:
    storage_t storage_{};
};