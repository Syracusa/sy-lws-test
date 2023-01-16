/*
Original source
https://github.com/iamscottmoyers/simple-libwebsockets-example/blob/master/server.c
 */


#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>

void hexdump(void *data, int len, FILE* stream)
{
   const int BYTE_INLINE = 16;
   char ascii_buf[BYTE_INLINE + 1];
   unsigned char *ptr = data;

   ascii_buf[BYTE_INLINE] = '\0';

   int linecount = 0;
   int lineoffset;
   for (int i = 0; i < len; i++)
   {
      lineoffset = i % BYTE_INLINE;

      /* Print offset if newline */
      if (lineoffset == 0)
         fprintf(stream, " %04x ", i);
      
      /* Add space at every 4 bytes.. */
      if (lineoffset % 4 == 0)
         fprintf(stream, " ");

      fprintf(stream, " %02x", ptr[i]);
      if ((ptr[i] < 0x20) || (ptr[i] > 0x7e))
         ascii_buf[lineoffset] = ' ';
      else
         ascii_buf[lineoffset] = ptr[i];

      /* Print ASCII if end of line */
      if (lineoffset == BYTE_INLINE - 1){
         fprintf(stream, "  %s\n", ascii_buf);
         linecount++;

         /* Print additional newline at every 5 lines */
         if (linecount != 0 && linecount % 5 == 0)
            fprintf(stream, "\n");
      }
   }

   ascii_buf[lineoffset + 1] = '\0';
   fprintf(stream, " %s\n", ascii_buf);
}

static int callback_http( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	switch( reason )
	{
		case LWS_CALLBACK_HTTP:
			lws_serve_http_file( wsi, "example.html", "text/html", NULL, 0 );
			break;
		case LWS_CALLBACK_RECEIVE:
			fprintf(stderr, "receive callback(%d)\n", reason);
			hexdump(in, len, stdout);
			break;
		default:
			fprintf(stderr, "callback reason %d\n", reason);
			break;
	}

	return 0;
}

#define EXAMPLE_RX_BUFFER_BYTES (10)
struct payload
{
	unsigned char data[LWS_SEND_BUFFER_PRE_PADDING + EXAMPLE_RX_BUFFER_BYTES + LWS_SEND_BUFFER_POST_PADDING];
	size_t len;
} received_payload;

static int callback_example( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	switch( reason )
	{
		case LWS_CALLBACK_RECEIVE:
			memcpy( &received_payload.data[LWS_SEND_BUFFER_PRE_PADDING], in, len );
			received_payload.len = len;
			lws_callback_on_writable_all_protocol( lws_get_context( wsi ), lws_get_protocol( wsi ) );
			break;

		case LWS_CALLBACK_SERVER_WRITEABLE:
			lws_write( wsi, &received_payload.data[LWS_SEND_BUFFER_PRE_PADDING], received_payload.len, LWS_WRITE_TEXT );
			break;

		default:
			break;
	}

	return 0;
}

enum protocols
{
	PROTOCOL_HTTP = 0,
	PROTOCOL_EXAMPLE,
	PROTOCOL_COUNT
};

static struct lws_protocols protocols[] =
{
	/* The first protocol must always be the HTTP handler */
	{
		"http-only",   /* name */
		callback_http, /* callback */
		0,             /* No per session data. */
		0,             /* max frame size / rx buffer */
	},
	{
		"example-protocol",
		callback_example,
		0,
		EXAMPLE_RX_BUFFER_BYTES,
	},
	{ NULL, NULL, 0, 0 } /* terminator */
};

int main( int argc, char *argv[] )
{
	struct lws_context_creation_info info;
	memset( &info, 0, sizeof(info) );

	info.port = 8764;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;

	struct lws_context *context = lws_create_context( &info );

	while( 1 )
	{
		lws_service( context, /* timeout_ms = */ 1000000 );
	}

	lws_context_destroy( context );

	return 0;
}