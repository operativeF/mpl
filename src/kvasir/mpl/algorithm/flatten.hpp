//          Copyright Chiel Douwes 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../sequence/join.hpp"

namespace kvasir {
	namespace mpl {
		namespace c {
			namespace detail {
				template <template <class...> class L, class T>
				struct flatten_element_impl {
					using type = L<T>;
				};

				template <template <class...> class L, class... Ts>
				struct flatten_element_impl<L, L<Ts...>> {
					using type = typename c::detail::join_select<c::detail::select_join_size(sizeof...(
						Ts))>::template f<list, typename flatten_element_impl<L, Ts>::type...>;
				};
			}
			template<typename SequenceType = lambda<list>, typename C = listify>
			struct flatten;
			
			template<template<typename...> class S, typename C>
			struct flatten<lambda<S>, C> {
				template<typename...Ts>
				using f = typename detail::join_select<detail::select_join_size(sizeof...(Ts))>::template f<C::template f,
					typename detail::flatten_element_impl<S, Ts>::type...>;
			};
		}

		namespace detail {
			template<typename T>
			struct flatten_impl;
			template<template<typename...> class S, typename...Ts>
			struct flatten_impl<S<Ts...>> {
				using type = typename c::flatten<lambda<S>>::template f<Ts...>;
			};
		}

		template <typename Sequence>
		using flatten = typename detail::flatten_impl<Sequence>::type;
	}
}
