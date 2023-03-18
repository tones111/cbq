#[no_mangle]
pub extern "C" fn cbq__construct() -> () {
    println!("todo: construct");
}

#[no_mangle]
pub extern "C" fn cbq__destruct() -> () {
    println!("todo: destruct");
}

//#[cfg(test)]
//mod tests {
//    use super::*;
//
//    #[test]
//    fn it_works() {
//        let result = add(2, 2);
//        assert_eq!(result, 4);
//    }
//}
