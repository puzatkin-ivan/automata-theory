﻿using Lekser;
using Lekser.Enums;
using SyntacticalAnalyzerGenerator.InsertActionsInSyntax.ASTNodes;
using SyntacticalAnalyzerGenerator.InsertActionsInSyntax.ASTNodes.Enums;
using System;
using System.Collections.Generic;
using System.Linq;

namespace SyntacticalAnalyzerGenerator.InsertActionsInSyntax
{
    public class ASTGenerator
    {
        private Stack<TermType> _signStack;
        private Stack<IASTNode> _nodesStack;

        private int _predictedUnaryMinusesCount = 0;
        private int _minusesWithBracketsCount = 0;

        private int _predictedNotSignCount = 0;
        private int _notSignsWithBracketsCount = 0;

        public IASTNode RootNode => _nodesStack.Peek();

        private List<IASTNode> _rootNodes = new List<IASTNode>();
        public IReadOnlyCollection<IASTNode> RootNodes => _rootNodes;

        public ASTGenerator()
        {
            _signStack = new Stack<TermType>();
            _nodesStack = new Stack<IASTNode>();
        }

        public void SaveAndClear()
        {
            if ( _nodesStack.Any() )
            {
                _rootNodes.Add( RootNode );
            }
            _nodesStack.Clear();
            _signStack.Clear();
            _predictedUnaryMinusesCount = 0;
            _minusesWithBracketsCount = 0;
            _predictedNotSignCount = 0;
            _notSignsWithBracketsCount = 0;
        }

        public void CreateLeafNode( Term number )
        {
            _nodesStack.Push( new LeafNode( number.Type, number.Value ) );
        }

        public bool CreateOperationNode( Term number )
        {
            if ( _signStack.Count == 0 )
                throw new ApplicationException( $"Error in sign sign stack empty: { number.Value } in row { number.RowPosition }." );

            IASTNode rightNode;
            IASTNode leftNode;
            var nodes = new List<IASTNode>();
            switch ( _signStack.Pop() )
            {
                case TermType.Plus:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.PlusNode, TermType.Plus, nodes ) );
                    break;
                case TermType.Minis:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.BinaryMinusNode, TermType.Minis, nodes ) );
                    break;
                case TermType.Multiple:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.MultipleNode, TermType.Multiple, nodes ) );
                    break;
                case TermType.Division:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.DivisionNode, TermType.Division, nodes ) );
                    break;
                default:
                    throw new ApplicationException( $"Operation not recognized. After:{ number.Value } in row { number.RowPosition }." );
            }

            return true;
        }

        public bool CreateBoolOperationNode( Term number )
        {
            if ( _signStack.Count == 0 || _signStack.Peek() == TermType.OpeningRoundBracket )
                return true;

            IASTNode rightNode;
            IASTNode leftNode;
            var nodes = new List<IASTNode>();
            switch ( _signStack.Pop() )
            {
                case TermType.Equal:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.Equal, TermType.Equal, nodes ) );
                    break;
                case TermType.NotEqual:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.NotEqual, TermType.NotEqual, nodes ) );
                    break;
                case TermType.Less:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.Less, TermType.Less, nodes ) );
                    break;
                case TermType.More:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.More, TermType.More, nodes ) );
                    break;
                case TermType.LessEqual:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.LessEqual, TermType.LessEqual, nodes ) );
                    break;
                case TermType.MoreEqual:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.MoreEqual, TermType.MoreEqual, nodes ) );
                    break;
                case TermType.And:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.LogicAnd, TermType.And, nodes ) );
                    break;
                case TermType.Or:
                    rightNode = _nodesStack.Pop();
                    leftNode = _nodesStack.Pop();
                    nodes.Add( leftNode );
                    nodes.Add( rightNode );
                    _nodesStack.Push( new TreeNode( NodeType.LogicOr, TermType.Or, nodes ) );
                    break;
                default:
                    throw new ApplicationException( $"Operation not recognized. After:{ number.Value } in row { number.RowPosition }." );
            }

            return true;
        }

        public void CreateUnaryMinusNode()
        {
            int unaryMinusesCountWithSingleNumber = _predictedUnaryMinusesCount - _minusesWithBracketsCount;
            if ( unaryMinusesCountWithSingleNumber > 0 )
            {
                _predictedUnaryMinusesCount--;
                var nodes = new List<IASTNode>();
                nodes.Add( _nodesStack.Pop() );

                _nodesStack.Push( new TreeNode( NodeType.UnaryMinusNode, TermType.Minis, nodes, "-" ) );
            }
        }

        public void CreateNotSignNode()
        {
            int notSignsCountWithSingleNumber = _predictedNotSignCount - _notSignsWithBracketsCount;
            if ( notSignsCountWithSingleNumber > 0 )
            {
                _predictedNotSignCount--;
                var nodes = new List<IASTNode>();
                nodes.Add( _nodesStack.Pop() );

                _nodesStack.Push( new TreeNode( NodeType.LogicNot, TermType.Not, nodes, "!" ) );
            }
        }

        public void UnaryNotSignFound()
        {
            _predictedNotSignCount++;
        }

        public void OpenBracketInBoolOpFound()
        {
            if ( _predictedNotSignCount > 0 )
            {
                _notSignsWithBracketsCount++;
            }
        }

        public void CloseBracketInBoolOpFound()
        {
            if ( _notSignsWithBracketsCount > 0 )
            {
                _notSignsWithBracketsCount--;
                _predictedNotSignCount--;
                var nodes = new List<IASTNode>();
                nodes.Add( _nodesStack.Pop() );

                _nodesStack.Push( new TreeNode( NodeType.LogicNot, TermType.Not, nodes, "!" ) );
            }
        }


        public void AddDeclarationNode( Term term )
        {
            switch ( term.Type )
            {
                case TermType.Int:
                case TermType.Float:
                case TermType.Bool:
                case TermType.Char:
                case TermType.Double:
                    _nodesStack.Push( new TreeNode( NodeType.DefineNewType, term.Type, new List<IASTNode>(), term.Value ) );
                    break;
                case TermType.Identifier:
                    IASTNode typeNode = _nodesStack.Pop();
                    typeNode.Nodes.Add( new LeafNode( TermType.Identifier, term.Value ) );
                    _nodesStack.Push( typeNode );
                    break;
                default:
                    break;
            }
        }

        public void AddLeafNode( Term term )
        {
            _nodesStack.Push( new LeafNode( term.Type, term.Value ) );
        }

        public void AddIfNode()
        {
            var nodes = new List<IASTNode>();
            while ( _nodesStack.Any() )
            {
                nodes.Add( _nodesStack.Pop() );
            }
            _nodesStack.Push( new TreeNode( NodeType.IfTerm, TermType.If, nodes ) );
        }

        public void AddWhileNode()
        {
            var nodes = new List<IASTNode>();
            while ( _nodesStack.Any() )
            {
                nodes.Add( _nodesStack.Pop() );
            }
            _nodesStack.Push( new TreeNode( NodeType.WhileTerm, TermType.While, nodes ) );
        }

        public void AddNode( IASTNode aSTNode )
        {
            _nodesStack.Push( aSTNode );
        }

        public void AddEchoNode()
        {
            var nodes = new List<IASTNode>();
            while ( _nodesStack.Any() )
            {
                nodes.Add( _nodesStack.Pop() );
            }
            if ( nodes.Count == 1 )
            {
                _nodesStack.Push( new TreeNode(
                    NodeType.Echoln,
                    TermType.Echoln,
                    new List<IASTNode>() )
                );
            }

            _nodesStack.Push( new TreeNode(
                NodeType.Echo,
                TermType.Echo,
                new List<IASTNode> { nodes[ 1 ], nodes[ 0 ] } )
            );
        }

        public void AddReadNode()
        {
            var nodes = new List<IASTNode>();
            while ( _nodesStack.Any() )
            {
                nodes.Add( _nodesStack.Pop() );
            }

            _nodesStack.Push( new TreeNode(
                NodeType.Read,
                TermType.Read,
                new List<IASTNode> { nodes[ 1 ], nodes[ 0 ] } )
            );
        }

        public void AddEqualityNode()
        {
            var nodes = new List<IASTNode>();
            while ( _nodesStack.Any() )
            {
                IASTNode node = _nodesStack.Pop();
                if ( _nodesStack.Any() )
                {
                    nodes.Add( node );
                }
                else
                {
                    nodes.Insert( 0, node );
                }
            }

            _nodesStack.Push( new TreeNode( NodeType.Equality, TermType.Equally, nodes, "=" ) );
        }

        public void UnaryMinusFound()
        {
            _predictedUnaryMinusesCount++;
        }

        public void AddSign( Term sign )
        {
            _signStack.Push( sign.Type );
        }

        public void RemoveSign( Term sign )
        {
            if ( sign.Type == TermType.ClosingRoundBracket )
            {
                if ( _signStack.Peek() == TermType.OpeningRoundBracket )
                {
                    _signStack.Pop();
                }
                else
                {
                    throw new ApplicationException( $"Found wrong term. when generating AST, After: { sign.Value } in row { sign.RowPosition }." );
                }
            }
        }


        public void OpenBracketFound()
        {
            if ( _predictedUnaryMinusesCount > 0 )
            {
                _minusesWithBracketsCount++;
            }
        }

        public void CloseBracketFound()
        {
            if ( _minusesWithBracketsCount > 0 )
            {
                _minusesWithBracketsCount--;
                _predictedUnaryMinusesCount--;
                var nodes = new List<IASTNode>();
                nodes.Add( _nodesStack.Pop() );

                _nodesStack.Push( new TreeNode( NodeType.UnaryMinusNode, TermType.Minis, nodes, "-" ) );
            }
        }
    }
}
