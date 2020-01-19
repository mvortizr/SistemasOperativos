import posix_ipc

posix_ipc.unlink_semaphore('/mutex')
posix_ipc.unlink_semaphore('/empty')
posix_ipc.unlink_semaphore('/full')