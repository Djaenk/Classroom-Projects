import {Cart} from '../models/Cart';
import { CartItem } from '../models/CartItem';

export class CartService {
    getCart() {
        return window.cart || new Cart();
    }

    addToCart(product) {
        let cart = window.cart || new Cart();
        let existing = cart.items.find(x => x.product.id == product.id);
        if (existing) {
            existing.quantity += 1;
            existing.totalPrice = existing.product.price * existing.quantity;
        } else {
            cart.items.push(new CartItem(product, 1, product.price));
        }

        cart.total = cart.items.map(x => x.totalPrice).reduce((x, y) => x + y);
        window.cart = cart;
    }
}

export default CartService;