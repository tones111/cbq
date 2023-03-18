#![allow(clippy::missing_safety_doc)]

use crossbeam::queue::ArrayQueue;

pub struct Cbq {
    q: ArrayQueue<u8>,
}

//impl Drop for Cbq {
//    fn drop(&mut self) {
//        println!("dropping Cbq");
//    }
//}

#[no_mangle]
pub extern "C" fn cbq__construct(cap: u32) -> *mut Cbq {
    Box::into_raw(Box::new(Cbq {
        q: ArrayQueue::new(usize::try_from(cap).unwrap()),
    }))
}

#[no_mangle]
pub unsafe extern "C" fn cbq__destruct(ptr: *mut Cbq) {
    drop(Box::from_raw(ptr))
}

#[no_mangle]
pub unsafe extern "C" fn cbq__push(ptr: *mut Cbq, val: u8) -> u8 {
    let cbq = &*ptr;
    cbq.q.push(val).is_ok().into()
}

#[no_mangle]
pub unsafe extern "C" fn cbq__pop(ptr: *mut Cbq, val: *mut u8) -> u8 {
    let cbq = &*ptr;
    match cbq.q.pop() {
        Some(v) => {
            *val = v;
            1
        }
        None => 0,
    }
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
