const queryString = window.location.search;

qs = queryString.split("%")


console.log(qs[1:]+qs[1].split(";"))