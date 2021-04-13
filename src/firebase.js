import firebase from "firebase";

var firebaseConfig = {
  apiKey: "AIzaSyCaKnDdJbUu2vUc4_WGwvUEaMbwRYXu3yI",
  authDomain: "iotmert.firebaseapp.com",
  databaseURL: "https://iotmert-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "iotmert",
  storageBucket: "iotmert.appspot.com",
  messagingSenderId: "90725113487",
  appId: "1:90725113487:web:d0f22a908976d2b1719afa",
  measurementId: "G-JJ5CFJ0SZ4",
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

export const db = firebase.database();
