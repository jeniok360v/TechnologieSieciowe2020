use HTTP::Daemon;
use HTTP::Response;
use HTTP::Status;

my $d = HTTP::Daemon->new(
        LocalAddr => 'localhost',
        LocalPort => 1900,
    ) || die;

print "Server running at: ", $d->url, "\n";

while (my $c = $d->accept) {
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {
            print $r->uri, "\n";
            my $str = $r->as_string;
            my $resp = HTTP::Response->new(200);
            $resp->header("MIME" => "text/html");
            $resp->content($str);
            $c->send_response($resp);
        }
        else {
            $c->send_error(RC_FORBIDDEN);
        }
    }
    $c->close;
    undef($c);
}