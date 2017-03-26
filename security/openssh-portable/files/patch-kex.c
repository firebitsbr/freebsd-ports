From ec165c392ca54317dbe3064a8c200de6531e89ad Mon Sep 17 00:00:00 2001
From: "markus@openbsd.org" <markus@openbsd.org>
Date: Mon, 10 Oct 2016 19:28:48 +0000
Subject: [PATCH] upstream commit

Unregister the KEXINIT handler after message has been
received. Otherwise an unauthenticated peer can repeat the KEXINIT and cause
allocation of up to 128MB -- until the connection is closed. Reported by
shilei-c at 360.cn

Upstream-ID: 43649ae12a27ef94290db16d1a98294588b75c05
---
 kex.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

diff --git kex.c kex.c
index 3f97f8c..6a94bc5 100644
--- kex.c
+++ kex.c
@@ -1,4 +1,4 @@
-/* $OpenBSD: kex.c,v 1.126 2016/09/28 21:44:52 djm Exp $ */
+/* $OpenBSD: kex.c,v 1.127 2016/10/10 19:28:48 markus Exp $ */
 /*
  * Copyright (c) 2000, 2001 Markus Friedl.  All rights reserved.
  *
@@ -481,6 +481,7 @@ kex_input_kexinit(int type, u_int32_t seq, void *ctxt)
 	if (kex == NULL)
 		return SSH_ERR_INVALID_ARGUMENT;
 
+	ssh_dispatch_set(ssh, SSH2_MSG_KEXINIT, NULL);
 	ptr = sshpkt_ptr(ssh, &dlen);
 	if ((r = sshbuf_put(kex->peer, ptr, dlen)) != 0)
 		return r;