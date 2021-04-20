import { ProductList } from './app/ProductList';
import { ProductDetails } from './app/ProductDetails';
import { MyCart } from './app/MyCart';

export const routes = [
    {path: "/", component: ProductList},
    {path: "/products/:productId", component: ProductDetails},
    {path: "/cart", component: MyCart}
]