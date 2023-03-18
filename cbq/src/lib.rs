#![allow(clippy::missing_safety_doc)]

use crossbeam::queue::ArrayQueue;

pub struct Cbq {
    q: ArrayQueue<Vec<u8>>,
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
pub unsafe extern "C" fn cbq__push(ptr: *mut Cbq, buf: *const u8, len: u32) -> u8 {
    let cbq = &*ptr;
    let buf = std::slice::from_raw_parts(buf, usize::try_from(len).unwrap());
    cbq.q.push(buf.to_vec()).is_ok().into()
}

#[no_mangle]
pub unsafe extern "C" fn cbq__force_push(ptr: *mut Cbq, buf: *const u8, len: u32) {
    let cbq = &*ptr;
    let buf = std::slice::from_raw_parts(buf, usize::try_from(len).unwrap());
    cbq.q.force_push(buf.to_vec());
}

#[no_mangle]
pub unsafe extern "C" fn cbq__pop(ptr: *mut Cbq, buf: *mut u8, len: u32) -> u32 {
    let cbq = &*ptr;
    match cbq.q.pop() {
        Some(v) => {
            let to_copy = std::cmp::min(v.len(), usize::try_from(len).unwrap());
            let buf = std::slice::from_raw_parts_mut(buf, usize::try_from(len).unwrap());
            buf[..to_copy].copy_from_slice(&v[..to_copy]);
            u32::try_from(to_copy).unwrap()
        }
        None => 0,
    }
}

#[no_mangle]
pub unsafe extern "C" fn cbq__capacity(ptr: *mut Cbq) -> u32 {
    let cbq = &*ptr;
    u32::try_from(cbq.q.capacity()).unwrap()
}

#[no_mangle]
pub unsafe extern "C" fn cbq__is_empty(ptr: *mut Cbq) -> u8 {
    let cbq = &*ptr;
    cbq.q.is_empty().into()
}

#[no_mangle]
pub unsafe extern "C" fn cbq__is_full(ptr: *mut Cbq) -> u8 {
    let cbq = &*ptr;
    cbq.q.is_full().into()
}

#[no_mangle]
pub unsafe extern "C" fn cbq__len(ptr: *mut Cbq) -> u32 {
    let cbq = &*ptr;
    u32::try_from(cbq.q.len()).unwrap()
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
