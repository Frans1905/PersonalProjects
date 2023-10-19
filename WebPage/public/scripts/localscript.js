window.addEventListener('pageshow', function (event) {
    var historyTraversal = event.persisted || (typeof window.performance != 'undefined' && window.performance.navigation.type === 2);
    if (historyTraversal) {
      this.document.location.href = '/';
    }
  });